# Dependencies #

| **Project**| **Version**|
|:-----------|:-----------|
|[QuantLib](http://quantlib.org)|1.2/1.3|
|[Gensrc](http://quantlib.org/gensrc/)|1.2.0|
|[ObjectHandler](http://quantlib.org/objecthandler/)|1.2.0|
|[QuantLibAddin for C++](http://quantlib.org/quantlibaddin/index.html)|1.2.0|

## Boost ##
```
 $ tar xvf boost_1_54_0.tar.gz
 $ cd boost_1_54_0/
 $ ./bootstrap.sh --prefix=$HOME --exec-prefix=$HOME
 $ ./b2 install
```

## [QuantLib](https://sourceforge.net/projects/quantlib/files/QuantLib/) ##
```
$ tar xvf QuantLib-1.2.1.tar.gz
$ cd QuantLib-1.2.1
$ ./configure --prefix=$HOME --exec-prefix=$HOME --with-boost-include=$HOME/include --with-boost-lib=$HOME/lib
$ make install
```

_**ObjectHandler** requires log4cxx which requires apr and apr-util.  Incase, log4cxx, apr and apr-utils are not installed on your host below are the steps to install them_
## Apr ##
```
$ tar xvf apr-1.4.6.tar.gz
$ cd apr-1.4.6/
$ ./configure --prefix=$HOME --exec-prefix=$HOME
$ make install
```

## Apr-Util ##
```
$ tar xvf apr-util-1.5.1.tar.gz
$ cd apr-util-1.5.1
$ ./configure --prefix=$HOME --exec-prefix=$HOME --with-apr=../apr-1.4.6
$ make install
```

## Log4cxx ##
```
$ tar xvf log4cxx-0.10.0d.tar.gz
$ cd log4cxx-0.10.0d
$ ./configure --prefix=$HOME --exec-prefix=$HOME --with-apr=../apr-1.4.6 --with-apr-util=../apr-util-1.5.1
$ make install
```

## [GenSrc](https://sourceforge.net/projects/quantlib/files/ObjectHandler/1.2.0/) ##
```
$ tar xvf gensrc-1.2.0.tar.gz
$ cd gensrc-1.2.0
$ ./configure --prefix=$HOME --exec-prefix=$HOME
$ make install
```

## [ObjectHandler](https://sourceforge.net/projects/quantlib/files/ObjectHandler/1.2.0/) ##
```
$ tar xvf ObjectHandler-1.2.0.tar.gz
$ cd ObjectHandler-1.2.0
$ export CPPFLAGS=-I$HOME/include
$ export LIBS=-L$HOME/lib
$ ./configure --prefix=$HOME --exec-prefix=$HOME --with-gensrc=../gensrc-1.2.0
$ make install
```


## [QuantLibAddin for C++](https://sourceforge.net/projects/quantlib/files/QuantLibAddin/1.2.0/) ##
```
$ tar xvf QuantLibAddin-1.2.0.tar.gz
$ cd QuantLibAddin-1.2.0
$ ./configure --prefix=$HOME --exec-prefix=$HOME --with-gensrc=../gensrc-1.2.0 --with-oh=../ObjectHandler-1.2.0 --enable-addin-cpp
$ make install
```