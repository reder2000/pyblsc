import timeit

import numpy
import sys
sys.path.append(r"C:\dev\qustrat\pyblsc\mybuild\Release")
#sys.path.append(r"C:\dev\qustrat\pyblsc\mybuild\RelWithDebInfo")

import pyblsc as ppp

# "CoP"_a, "S"_a, "X"_a, "R"_a, "Q"_a, "Trate"_a, "Tsigma"_a, "sig"_a
line1 = [1.,1.,1.,0.05,0.01,1.,0.99,0.3]
line2 = [-1.,1.,1.,0.05,0.01,1.,0.99,0.3]
line3 = [1.,1.1,1.,0.05,0.01,1.,0.99,0.3]

print(ppp.bls_price(*line1))
print(ppp.bls_price(*line2))
print(ppp.bls_price(*line3))

def f0():
    for i in range(7*5*2):
        ppp.bls_price(*line1)
        ppp.bls_price(*line2)
        ppp.bls_price(*line3)
        #print(res)

def f1():
    params= numpy.array([line1,line2,line3])
    res = numpy.array([numpy.nan] * params.shape[0])
    for i in range(7*5*2):
        ppp.bls_prices(res, params)

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
         line2, line3, line1, line2, line3,])
    res = numpy.array([numpy.nan]*params.shape[0])
    ppp.bls_prices(res,params)


nruns = 12345
nbcalcs = 2*5*21*nruns
print (nbcalcs/  timeit.Timer(f0).timeit(number=nruns)  )
print (nbcalcs/ timeit.Timer(f1).timeit(number=nruns) )
print (nbcalcs/     timeit.Timer(f2).timeit(number=nruns) )

