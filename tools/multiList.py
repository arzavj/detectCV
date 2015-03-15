from __future__ import print_function
import os
import numpy as np
import re
nTest = 100
nVal = 100
print ('Using nTest = %d, nVal = %d\n' % (nTest, nVal))
pwd = os.getcwd()
f_train = open('train_listfile.txt', 'wb')
f_test = open('test_listfile.txt', 'wb')
f_val = open('val_listfile.txt', 'wb')

labels = ['bike', 'bus', 'car', 'dog', 'motorbike', 'others', 'pedestrian', 'skater', 'stroller']
counts = [0]*len(labels)

for file in os.listdir("."):
  for i in xrange(len(labels)):
    if file.startswith(labels[i]):
      counts[i] += 1
      break

testSets = []
valSets = []
for i in xrange(len(labels)):
  perms = np.random.permutation(counts[i])+1
  testSets.append(perms[0: nTest])
  valSets.append(perms[nTest: nTest+nVal])

assignCounts = [0]*len(labels)
regex = re.compile(r'\d+')
for file in os.listdir("."):
  for i in xrange(len(labels)):
    if file.startswith(labels[i]):
      num = int(regex.findall(file)[0])
      if num in testSets[i]:
        f_test.write('%s %d\n' % (file, i))
      elif num in valSets[i]:
        f_val.write('%s %d\n' % (file, i))
      else:
        f_train.write('%s %d\n' % (file, i))

f_test.close()
f_val.close()
f_train.close()
