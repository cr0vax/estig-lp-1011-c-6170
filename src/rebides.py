# This file was automatically generated by SWIG (http://www.swig.org).
# Version 1.3.40
#
# Do not make changes to this file unless you know what you are doing--modify
# the SWIG interface file instead.
# This file is compatible with both classic and new-style classes.

from sys import version_info
if version_info >= (2,6,0):
    def swig_import_helper():
        from os.path import dirname
        import imp
        fp = None
        try:
            fp, pathname, description = imp.find_module('_rebides', [dirname(__file__)])
        except ImportError:
            import _rebides
            return _rebides
        if fp is not None:
            try:
                _mod = imp.load_module('_rebides', fp, pathname, description)
            finally:
                fp.close()
            return _mod
    _rebides = swig_import_helper()
    del swig_import_helper
else:
    import _rebides
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
    if (not static) or hasattr(self,name):
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



def count_teachers(*args):
  return _rebides.count_teachers(*args)
count_teachers = _rebides.count_teachers

def count_teachers_per_establishment(*args):
  return _rebides.count_teachers_per_establishment(*args)
count_teachers_per_establishment = _rebides.count_teachers_per_establishment

def count_teachers_per_degree(*args):
  return _rebides.count_teachers_per_degree(*args)
count_teachers_per_degree = _rebides.count_teachers_per_degree

def count_teachers_per_degree_establishment(*args):
  return _rebides.count_teachers_per_degree_establishment(*args)
count_teachers_per_degree_establishment = _rebides.count_teachers_per_degree_establishment

def list_establishments_per_year(*args):
  return _rebides.list_establishments_per_year(*args)
list_establishments_per_year = _rebides.list_establishments_per_year

def list_teachers_per_degree_year(*args):
  return _rebides.list_teachers_per_degree_year(*args)
list_teachers_per_degree_year = _rebides.list_teachers_per_degree_year

def list_teachers_leaving_institution_year(*args):
  return _rebides.list_teachers_leaving_institution_year(*args)
list_teachers_leaving_institution_year = _rebides.list_teachers_leaving_institution_year

def list_new_teachers_institution_year(*args):
  return _rebides.list_new_teachers_institution_year(*args)
list_new_teachers_institution_year = _rebides.list_new_teachers_institution_year

def count_teachers_to_file():
  return _rebides.count_teachers_to_file()
count_teachers_to_file = _rebides.count_teachers_to_file

def count_teachers_per_establishment_to_file():
  return _rebides.count_teachers_per_establishment_to_file()
count_teachers_per_establishment_to_file = _rebides.count_teachers_per_establishment_to_file

def count_teachers_per_degree_to_file():
  return _rebides.count_teachers_per_degree_to_file()
count_teachers_per_degree_to_file = _rebides.count_teachers_per_degree_to_file

def count_teachers_per_degree_establishment_to_file():
  return _rebides.count_teachers_per_degree_establishment_to_file()
count_teachers_per_degree_establishment_to_file = _rebides.count_teachers_per_degree_establishment_to_file

def list_establishments_per_year_to_file():
  return _rebides.list_establishments_per_year_to_file()
list_establishments_per_year_to_file = _rebides.list_establishments_per_year_to_file

def list_teachers_per_degree_year_to_file():
  return _rebides.list_teachers_per_degree_year_to_file()
list_teachers_per_degree_year_to_file = _rebides.list_teachers_per_degree_year_to_file

def list_teachers_leaving_institution_year_to_file():
  return _rebides.list_teachers_leaving_institution_year_to_file()
list_teachers_leaving_institution_year_to_file = _rebides.list_teachers_leaving_institution_year_to_file

def list_new_teachers_institution_year_to_file():
  return _rebides.list_new_teachers_institution_year_to_file()
list_new_teachers_institution_year_to_file = _rebides.list_new_teachers_institution_year_to_file


