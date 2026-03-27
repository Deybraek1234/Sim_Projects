import numpy as np
import matplotlib.pyplot as plt

nb = 5
m = 5000
sigma = 1/np.sqrt(12)
Q = np.zeros(m)
media = np.zeros(m)
for i in range(m): 
    x=np.random.uniform(0,1,nb)
    media[i]=np.sum(x)/nb
    Q[i]=(media[i]-0.5)/(sigma/np.sqrt(nb))
_,bordi, _ = plt.hist(Q, bins = 80, edgecolor = 'k', range=(-4,4))
deltak = bordi[1]-bordi[0]
centri = np.zeros(80)
y = np.zeros(80)
def gaussiana(x,mu):
    return(1/(sigma*np.sqrt(2*np.pi)))*np.exp(-((x-mu))**2 / (2 * sigma**2))
for i in range(80):
    centri[i] = bordi[i]+deltak/2
    y[i] = gaussiana(centri[i:Q0)*m*deltak
print(len(Q))
plt.plot(centri,y,'o')
plt.show()