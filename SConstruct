import os
import sys
import time
import glob

def UseClang(env):
    env.Replace(CC='clang')
    env.Replace(CXX='clang++')

# Build Vars 
INSTALL_DIR = 'build'
PATH        = []
PLATFORM    = []
ROOT        = []
CCFLAGS     = ['-std=c++11', '-DAPPROX_MSG_SIZE=4096', '-DMAX_PROC_MSGS=100']
CPPPATH     = ['.', '..', '#rplib', '#dropscheduler']
LIBS        = []
LIBPATH     = ['#rplib', '#droplib']
LINKFLAGS   = []

# Build Platform
if sys.platform.startswith('win'):
    PLATFORM = 'win'

elif sys.platform == 'darwin':
    PLATFORM = 'darwin'

else:
    PLATFORM = 'linux'

# Target Platform
if sys.platform.startswith('win') or ARGUMENTS.get('use_mingw', 0):
    TARGET = 'win'

elif sys.platform == 'darwin':
    TARGET = 'darwin'

else:
    TARGET = 'linux'

# Target flags and deps
if TARGET == 'win' and PLATFORM == 'win':
    CCFLAGS.extend(['/DOS_WIN=1','/EHsc', '/MT']) 

elif TARGET == 'win' and PLATFORM == 'linux':
    CCFLAGS.append('-DOS_WIN=1')

elif PLATFORM == 'darwin':
    CCFLAGS.append('-DOS_MACOSX=1')

elif PLATFORM == 'linux':
    CCFLAGS.append('-DOS_LINUX=1')

# Debug Options
if ARGUMENTS.get('debug', 0):
    CCFLAGS.append('-DRP_STRIP_LOG=0')
    if (PLATFORM =='win'):
      CCFLAGS.append('/Zi')
      LINKFLAGS.extend(['/INCREMENTAL:NO','/DEBUG','/OPT:REF','/OPT:ICF'])
    else:
      CCFLAGS.append('-g')

if ARGUMENTS.get('optimise', 0):
    CCFLAGS.append('-O3')
    
if not ARGUMENTS.get('use_mingw', 0):
    env = Environment(
        PLATFORM  = PLATFORM,
        ROOT      = ROOT,
        CCFLAGS   = CCFLAGS,
        CPPPATH   = CPPPATH,
        LIBS      = LIBS,
        LIBPATH   = LIBPATH,
        LINKFLAGS = LINKFLAGS
    )
else:
    CPPPATH.append(ARGUMENTS.get('cpppath', 0))
    PATH.extend(['./mxe/usr/bin', './mxe/usr/i686-w64-mingw32/qt/bin'])
    env = Environment(
        PLATFORM  = PLATFORM,
        ROOT      = ROOT,
        CCFLAGS   = CCFLAGS,
        CPPPATH   = [CPPPATH, './mxe/usr/i686-w64-mingw32/include'],
        LIBS      = [LIBS],
        LIBPATH   = LIBPATH,
        WINDRES   = 'i686-w64-mingw32-windres',
        CC     = 'i686-w64-mingw32-gcc',
        CXX    = 'i686-w64-mingw32-g++',
        AR     = 'i686-w64-mingw32-ar',
        RANLIB = 'i686-w64-mingw32-ranlib',
        LINKFLAGS=['-static-libgcc', '-static-libstdc++', '-Wl,-subsystem,windows']
    )
    env['ENV']['PATH'] = ''.join(['%s:' % p for p in PATH]) + env['ENV']['PATH']
    env.MergeFlags(['!i686-w64-mingw32-pkg-config opencv --cflags --libs'])
    env.MergeFlags(['!i686-w64-mingw32-pkg-config QtGui --cflags --libs'])

# Clang compiler
if int(ARGUMENTS.get('use_clang', 0)):
    UseClang(env)

Export('env')

[rplibstatic, rplib, rpdeps] = env.SConscript('rplib/SConstruct')
[droplib, dldeps, dlplugins] = env.SConscript('droplib/SConstruct', exports='rplib rpdeps')
[app] = env.SConscript('dropapp/SConstruct', exports='env droplib rplib')

install = [
    Execute(Mkdir(INSTALL_DIR)),
    env.Install(INSTALL_DIR, rplib),
    env.Install(INSTALL_DIR, droplib),
    env.Install(INSTALL_DIR, dlplugins),
    env.Install(INSTALL_DIR, app),
    env.Install(INSTALL_DIR+'/res', Glob('dropapp/res/*.*'))
]

Default(app)

Depends(droplib, rplib)
Alias('install', install)

