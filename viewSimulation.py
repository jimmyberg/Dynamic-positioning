import csv
import numpy as np
import matplotlib.pyplot as plt

f = open('data.csv', 'rb')
reader = csv.reader(f, delimiter=',')
headers = reader.next()

data = {}

for h in headers:
    data[h] = []

for row in reader:
    for h, v in zip(headers,row):
        data[h].append(np.float(v))

plt.figure(1)
plt.subplot(221)
plt.legend(plt.plot(data['time'], data['x'], 'r',
                    data['time'], data['y'], 'b'),
           ['x', 'y'])
plt.axhline(0, color='black')

plt.subplot(222)
plt.legend(plt.plot(data['time'], data['thruster0rotation'], 'g',
                    data['time'], data['thruster1rotation'], 'y'),
           ["thrust0rot", "thrust1rot"])
plt.axhline(0, color='black')

plt.subplot(223)
plt.legend(plt.plot(data['time'], data['thrust0'], 'b',
                    data['time'], data['thrust1'], 'r'),
           ["thrust0", "thrust1"])
plt.axhline(0, color='black')

plt.subplot(224)
plt.legend(plt.plot(data['time'], data['errorX'], 'r',
                    data['time'], data['errorY'], 'g',
                    data['time'], data['errorH'], 'b'),
           ["errorX", "errorY", "errorH"])
plt.axhline(0, color='black')

plt.show()
