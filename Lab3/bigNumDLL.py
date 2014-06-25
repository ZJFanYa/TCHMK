# This file was automatically generated by SWIG (http://www.swig.org).
# Version 3.0.0
#
# Do not make changes to this file unless you know what you are doing--modify
# the SWIG interface file instead.





from sys import version_info
if version_info >= (2,6,0):
    def swig_import_helper():
        from os.path import dirname
        import imp
        fp = None
        try:
            fp, pathname, description = imp.find_module('_bigNumDLL', [dirname(__file__)])
        except ImportError:
            import _bigNumDLL
            return _bigNumDLL
        if fp is not None:
            try:
                _mod = imp.load_module('_bigNumDLL', fp, pathname, description)
            finally:
                fp.close()
            return _mod
    _bigNumDLL = swig_import_helper()
    del swig_import_helper
else:
    import _bigNumDLL
del version_info
try:
    _swig_property = property
except NameError:
    pass # Python < 2.2 doesn't have 'property'.
def _swig_setattr_nondynamic(self,class_type,name,value,static=1):
    if (name == "thisown"): return self.this.own(value)
    if (name == "this"):
        if type(value).__name__ == 'SwigPyObject':
            self.__dict__[name] = value
            return
    method = class_type.__swig_setmethods__.get(name,None)
    if method: return method(self,value)
    if (not static):
        self.__dict__[name] = value
    else:
        raise AttributeError("You cannot add attributes to %s" % self)

def _swig_setattr(self,class_type,name,value):
    return _swig_setattr_nondynamic(self,class_type,name,value,0)

def _swig_getattr(self,class_type,name):
    if (name == "thisown"): return self.this.own()
    method = class_type.__swig_getmethods__.get(name,None)
    if method: return method(self)
    raise AttributeError(name)

def _swig_repr(self):
    try: strthis = "proxy of " + self.this.__repr__()
    except: strthis = ""
    return "<%s.%s; %s >" % (self.__class__.__module__, self.__class__.__name__, strthis,)

try:
    _object = object
    _newclass = 1
except AttributeError:
    class _object : pass
    _newclass = 0


class bigNum(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, bigNum, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, bigNum, name)
    __repr__ = _swig_repr
    def __init__(self, *args): 
        this = _bigNumDLL.new_bigNum(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _bigNumDLL.delete_bigNum
    __del__ = lambda self : None;
    def __add__(self, *args): return _bigNumDLL.bigNum___add__(self, *args)
    def __sub__(self, *args): return _bigNumDLL.bigNum___sub__(self, *args)
    def __mul__(self, *args): return _bigNumDLL.bigNum___mul__(self, *args)
    def __div__(self, *args): return _bigNumDLL.bigNum___div__(self, *args)
    def __xor__(self, *args): return _bigNumDLL.bigNum___xor__(self, *args)
    def __mod__(self, *args): return _bigNumDLL.bigNum___mod__(self, *args)
    def __eq__(self, *args): return _bigNumDLL.bigNum___eq__(self, *args)
    def __ne__(self, *args): return _bigNumDLL.bigNum___ne__(self, *args)
    def __ge__(self, *args): return _bigNumDLL.bigNum___ge__(self, *args)
    def __le__(self, *args): return _bigNumDLL.bigNum___le__(self, *args)
    def __gt__(self, *args): return _bigNumDLL.bigNum___gt__(self, *args)
    def __lt__(self, *args): return _bigNumDLL.bigNum___lt__(self, *args)
    def Read(self, *args): return _bigNumDLL.bigNum_Read(self, *args)
    def Write(self, *args): return _bigNumDLL.bigNum_Write(self, *args)
bigNum_swigregister = _bigNumDLL.bigNum_swigregister
bigNum_swigregister(bigNum)

# This file is compatible with both classic and new-style classes.


