import os, sys

pythons = os.environ['PYTHONS']
print 'Pythons folder = "%s"' % pythons

for python in os.listdir( pythons):
   if python[0] == '.' or python[0] == '-': continue
   pythondir = os.path.join( pythons, python )
   if not os.path.isdir( pythondir): continue
   print 'Python = "%s"' % python

   pythonlib = 'python' + python[0:2]
   qt = os.environ['QTS']
   arch = 'amd64'
   if python.find('32') >= 2:
      qt += '-32'
      arch = 'x86'

   os.environ['QTDIR'] = qt
   os.environ['AF_PYAFVER'] = python
   os.environ['PYTHONDIR'] = pythondir
   os.environ['PYTHONLIB'] = pythonlib

   cmd = 'make_pyaf.cmd ' + arch
   os.system( cmd)
