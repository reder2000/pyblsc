import timeit

import numpy
import sys
sys.path.append(r"C:\dev\qustrat\pybs\mybuild\Release")
#sys.path.append(r"C:\dev\qustrat\pybs\mybuild\RelWithDebInfo")

import pybs as ppp

# "CoP"_a, "S"_a, "X"_a, "R"_a, "Trate"_a, "Tsigma"_a, "sig"_a
line1 = [1.,1.,1.,0.05,1.,0.99,0.3]
line2 = [-1.,1.,1.,0.05,1.,0.99,0.3]
line3 = [1.,1.1,1.,0.05,1.,0.99,0.3]

print(ppp.bls_price_noq(*line1))
print(ppp.bls_price_noq(*line2))
print(ppp.bls_price_noq(*line3))

def f0():
    for i in range(7*5*2):
        ppp.bls_price_noq(*line1)
        ppp.bls_price_noq(*line2)
        ppp.bls_price_noq(*line3)
        #print(res)

def f1():
    params= numpy.array([line1,line2,line3,line1,line2,line3])
    res = numpy.array([numpy.nan] * params.shape[0])
    for i in range(7*5):
        ppp.bls_prices_noq(res, params)

def f2():
    #params = numpy.array([line1,line2,line3,line1,line2,line3,line1,line2,line3,line1,line2,line3,line1,line2,line3,line1,line2,line3,line1,line2,line3])
    params = numpy.array(
        [line1, line2, line3, line1, line2, line3, line1, line2, line3, line1, line2, line3, line1, line2, line3, line1,
         line2, line3, line1, line2, line3,line1, line2, line3, line1, line2, line3, line1, line2, line3, line1, line2, line3, line1, line2, line3, line1,
         line2, line3, line1, line2, line3,line1, line2, line3, line1, line2, line3, line1, line2, line3, line1, line2, line3, line1, line2, line3, line1,
         line2, line3, line1, line2, line3,line1, line2, line3, line1, line2, line3, line1, line2, line3, line1, line2, line3, line1, line2, line3, line1,
         line2, line3, line1, line2, line3,line1, line2, line3, line1, line2, line3, line1, line2, line3, line1, line2, line3, line1, line2, line3, line1,
         line2, line3, line1, line2, line3,line1, line2, line3, line1, line2, line3, line1, line2, line3, line1, line2, line3, line1, line2, line3, line1,
         line2, line3, line1, line2, line3,line1, line2, line3, line1, line2, line3, line1, line2, line3, line1, line2, line3, line1, line2, line3, line1,
         line2, line3, line1, line2, line3,line1, line2, line3, line1, line2, line3, line1, line2, line3, line1, line2, line3, line1, line2, line3, line1,
         line2, line3, line1, line2, line3,line1, line2, line3, line1, line2, line3, line1, line2, line3, line1, line2, line3, line1, line2, line3, line1,
         line2, line3, line1, line2, line3,line1, line2, line3, line1, line2, line3, line1, line2, line3, line1, line2, line3, line1, line2, line3, line1,
         line2, line3, line1, line2, line3,],dtype=float)
    res = numpy.array([numpy.nan]*params.shape[0])
    ppp.bls_prices_noq(res,params)

def f3():
    #params = numpy.array([line1,line2,line3,line1,line2,line3,line1,line2,line3,line1,line2,line3,line1,line2,line3,line1,line2,line3,line1,line2,line3])
    params = numpy.array(
        [line1, line2, line3, line1, line2, line3, line1, line2, line3, line1, line2, line3, line1, line2, line3, line1,
         line2, line3, line1, line2, line3,line1, line2, line3, line1, line2, line3, line1, line2, line3, line1, line2, line3, line1, line2, line3, line1,
         line2, line3, line1, line2, line3,line1, line2, line3, line1, line2, line3, line1, line2, line3, line1, line2, line3, line1, line2, line3, line1,
         line2, line3, line1, line2, line3,line1, line2, line3, line1, line2, line3, line1, line2, line3, line1, line2, line3, line1, line2, line3, line1,
         line2, line3, line1, line2, line3,line1, line2, line3, line1, line2, line3, line1, line2, line3, line1, line2, line3, line1, line2, line3, line1,
         line2, line3, line1, line2, line3,line1, line2, line3, line1, line2, line3, line1, line2, line3, line1, line2, line3, line1, line2, line3, line1,
         line2, line3, line1, line2, line3,line1, line2, line3, line1, line2, line3, line1, line2, line3, line1, line2, line3, line1, line2, line3, line1,
         line2, line3, line1, line2, line3,line1, line2, line3, line1, line2, line3, line1, line2, line3, line1, line2, line3, line1, line2, line3, line1,
         line2, line3, line1, line2, line3,line1, line2, line3, line1, line2, line3, line1, line2, line3, line1, line2, line3, line1, line2, line3, line1,
         line2, line3, line1, line2, line3,line1, line2, line3, line1, line2, line3, line1, line2, line3, line1, line2, line3, line1, line2, line3, line1,
         line2, line3, line1, line2, line3,]).transpose()
    res = numpy.array([numpy.nan]*params.shape[1])
    ppp.bls_prices_noq_mkl(res,params)

if 0 :
    nruns = 12345
    nbcalcs = 2*5*21*nruns
    print (nbcalcs/  timeit.Timer(f0).timeit(number=nruns)  )
    print (nbcalcs/ timeit.Timer(f1).timeit(number=nruns) )
    print (nbcalcs/     timeit.Timer(f2).timeit(number=nruns) )
    print (nbcalcs/     timeit.Timer(f3).timeit(number=nruns) )


def f(res,params):
    # params= numpy.array([line1]*n)
    # res = numpy.array([numpy.nan] * params.shape[0])
    ppp.bls_prices_noq(res, params)

def ff(n:int):  
    for i in range(n):
        ppp.bls_price_noq(*line1)


nruns = 100
for n in range(1,10000,50):
    params= numpy.array([line1]*n)
    res = numpy.array([numpy.nan] * params.shape[0])
    print(n,int(nruns*n / timeit.Timer(lambda :f(res,params)).timeit(number=nruns)/1000) ,'k')
