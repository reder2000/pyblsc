import timeit

import numpy
import sys
sys.path.append(r"C:\dev\qustrat\pybslc\mybuild\Release")
#sys.path.append(r"C:\dev\qustrat\pybslc\mybuild\RelWithDebInfo")
#sys.path.append(r"C:\dev\qustrat\pyblsc\mybuild")
#import pyblsc as ppp
# import mybuild.Release.pyblsc as pyblsc
# from mybuild.Release.pyblsc import BSGreeks as Gr
#from mybuild.RelWithDebInfo.pyblsc import BSGreeks as Gr
#import mybuild.Release.pyblsc as pyblsc
import pyblsc
from pyblsc import  BSGreeks as Gr
#from mybuild.Release.pyblsc import BSGreeks as Gr

# "CoP"_a, "S"_a, "X"_a, "R"_a, "Trate"_a, "Tsigma"_a, "sig"_a
# 1.(greek: BSGreeks, CoP: float, F: float, X: float, df: float, Tsigma: float, sig: float) -> float
CoP=1 ; F=1.15 ; X=1.05 ; df=0.95 ; Tsigma=1.23 ; sig= 0.3
CoP=-1 ; F=2252.6 ; X=  1100 ; df=1.00001 ; Tsigma=0.2 ; sig= 0.5366
line1 = [-1,F,X,df,Tsigma,sig]
line2 = [1,F,X,df,Tsigma,sig]

p = pyblsc.FBlsGreek(Gr.price, *line1)
c = pyblsc.FBlsGreek(Gr.price,*line2)
line3 = [-1,F,X,df,Tsigma,p]
line4 = [1,F,X,df,Tsigma,c]
print(pyblsc.FBlsGreek(Gr.implied_volatility_jackel,*line3))
print(pyblsc.FBlsGreek(Gr.implied_volatility_jackel,*line4))

def blsprice_loop(n, _): # 1.8 M opt / sec
     # for i in range(n//2+1):
     for i in range(n):
        pyblsc.FBlsGreek(Gr.price, *line1)
         # pyblsc.FBlsGreek(Gr.price, *line2)

def blsprice_seq(params,res,n):  # 52.8 M opt / sec
    if n:
        params = list(line1)
        if 1:
            params[2] = numpy.array([ params[2]] * n )
            params[-1] = numpy.array([params[-1]] * n)
        else:
            params[2] = [_params[2]] * n  # list(numpy.array([ params[2]] * n ))
            params[-1] = [_params[-1]] * n  # list(numpy.array([params[-1]] * n))
        # params += [False]
        res = numpy.array([0.]*n)
        return params,res
    pyblsc.FBlsGreeks_seq(Gr.price,*params)


def blsprice_inv_seq(params,res,n):  # 52.8 M opt / sec
    if n:
        params = list(line3)
        if 1:
            params[2] = numpy.array([ params[2]] * n )
            params[-1] = numpy.array([params[-1]] * n)
        else:
            params[2] = [params[2]]*n # list(numpy.array([ params[2]] * n ))
            params[-1] = [params[-1]]*n # list(numpy.array([params[-1]] * n))
        # params += [False]
        res = numpy.array([0.]*n)
        return params,res
    pyblsc.FBlsGreeks_seq(res,Gr.implied_volatility_jackel,*params)


# def f1():
#     params= numpy.array([line1,line2,line3,line1,line2,line3])
#     res = numpy.array([numpy.nan] * params.shape[0])
#     for i in range(7*5):
#         ppp.bls_prices_noq(res, params)
#
# def f2():
#     #params = numpy.array([line1,line2,line3,line1,line2,line3,line1,line2,line3,line1,line2,line3,line1,line2,line3,line1,line2,line3,line1,line2,line3])
#     params = numpy.array(
#         [line1, line2, line3, line1, line2, line3, line1, line2, line3, line1, line2, line3, line1, line2, line3, line1,
#          line2, line3, line1, line2, line3,line1, line2, line3, line1, line2, line3, line1, line2, line3, line1, line2, line3, line1, line2, line3, line1,
#          line2, line3, line1, line2, line3,line1, line2, line3, line1, line2, line3, line1, line2, line3, line1, line2, line3, line1, line2, line3, line1,
#          line2, line3, line1, line2, line3,line1, line2, line3, line1, line2, line3, line1, line2, line3, line1, line2, line3, line1, line2, line3, line1,
#          line2, line3, line1, line2, line3,line1, line2, line3, line1, line2, line3, line1, line2, line3, line1, line2, line3, line1, line2, line3, line1,
#          line2, line3, line1, line2, line3,line1, line2, line3, line1, line2, line3, line1, line2, line3, line1, line2, line3, line1, line2, line3, line1,
#          line2, line3, line1, line2, line3,line1, line2, line3, line1, line2, line3, line1, line2, line3, line1, line2, line3, line1, line2, line3, line1,
#          line2, line3, line1, line2, line3,line1, line2, line3, line1, line2, line3, line1, line2, line3, line1, line2, line3, line1, line2, line3, line1,
#          line2, line3, line1, line2, line3,line1, line2, line3, line1, line2, line3, line1, line2, line3, line1, line2, line3, line1, line2, line3, line1,
#          line2, line3, line1, line2, line3,line1, line2, line3, line1, line2, line3, line1, line2, line3, line1, line2, line3, line1, line2, line3, line1,
#          line2, line3, line1, line2, line3,],dtype=float)
#     res = numpy.array([numpy.nan]*params.shape[0])
#     ppp.bls_prices_noq(res,params)
#
# def f3():
#     #params = numpy.array([line1,line2,line3,line1,line2,line3,line1,line2,line3,line1,line2,line3,line1,line2,line3,line1,line2,line3,line1,line2,line3])
#     params = numpy.array(
#         [line1, line2, line3, line1, line2, line3, line1, line2, line3, line1, line2, line3, line1, line2, line3, line1,
#          line2, line3, line1, line2, line3,line1, line2, line3, line1, line2, line3, line1, line2, line3, line1, line2, line3, line1, line2, line3, line1,
#          line2, line3, line1, line2, line3,line1, line2, line3, line1, line2, line3, line1, line2, line3, line1, line2, line3, line1, line2, line3, line1,
#          line2, line3, line1, line2, line3,line1, line2, line3, line1, line2, line3, line1, line2, line3, line1, line2, line3, line1, line2, line3, line1,
#          line2, line3, line1, line2, line3,line1, line2, line3, line1, line2, line3, line1, line2, line3, line1, line2, line3, line1, line2, line3, line1,
#          line2, line3, line1, line2, line3,line1, line2, line3, line1, line2, line3, line1, line2, line3, line1, line2, line3, line1, line2, line3, line1,
#          line2, line3, line1, line2, line3,line1, line2, line3, line1, line2, line3, line1, line2, line3, line1, line2, line3, line1, line2, line3, line1,
#          line2, line3, line1, line2, line3,line1, line2, line3, line1, line2, line3, line1, line2, line3, line1, line2, line3, line1, line2, line3, line1,
#          line2, line3, line1, line2, line3,line1, line2, line3, line1, line2, line3, line1, line2, line3, line1, line2, line3, line1, line2, line3, line1,
#          line2, line3, line1, line2, line3,line1, line2, line3, line1, line2, line3, line1, line2, line3, line1, line2, line3, line1, line2, line3, line1,
#          line2, line3, line1, line2, line3,]).transpose()
#     res = numpy.array([numpy.nan]*params.shape[1])
#     ppp.bls_prices_noq_mkl(res,params)
#
# if 0 :
#     nruns = 12345
#     nbcalcs = 2*5*21*nruns
#     print (nbcalcs/  timeit.Timer(f0).timeit(number=nruns)  )
#     print (nbcalcs/ timeit.Timer(f1).timeit(number=nruns) )
#     print (nbcalcs/     timeit.Timer(f2).timeit(number=nruns) )
#     print (nbcalcs/     timeit.Timer(f3).timeit(number=nruns) )
#
#
# def f(res,params):
#     # params= numpy.array([line1]*n)
#     # res = numpy.array([numpy.nan] * params.shape[0])
#     ppp.bls_prices_noq(res, params)
#     # ppp.bls_prices_noq_mkl(res, params)
#
# def ff(n:int):
#     for i in range(n):
#         ppp.bls_price_noq(*line1)


nruns = 10000
for n in range(1,100,1):
    if 0 : # single call / loop
        # single call is almost already full speed
        print(n, int(nruns * n / timeit.Timer(lambda : blsprice_loop(n, None)).timeit(number=nruns) / 1000), 'k')
    if  0:       # multi call / loop
        # // better > 500
        params,res =  blsprice_seq(0,0,n)
        print(n, int(nruns * n / timeit.Timer(lambda: blsprice_seq(params,res,0)).timeit(number=nruns) / (1000)), 'k')
        params[-1] = True
        print(n, int(nruns * n / timeit.Timer(lambda: blsprice_seq(params,res,0)).timeit(number=nruns) / (1000)), 'k')
    if 1:
        # // better > 20 (ivol)
        params,res =  blsprice_inv_seq(0,0,n)
        print(n, int(nruns * n / timeit.Timer(lambda: blsprice_inv_seq(params,res,0)).timeit(number=nruns) / (1000)), 'k')
        # params[-1] = True
        print(n, int(nruns * n / timeit.Timer(lambda: blsprice_inv_seq(params,res,0)).timeit(number=nruns) / (1000)), 'k')

