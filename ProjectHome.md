## QLDDS - Data Distribution Service for  [QuantLib](http://quantlib.org) ##

QLDDS is an open source project that simplifies the use of [QuantLib](http://quantlib.org) in the distributed realtime environment via [OpenDDS](http://opendds.org).

Using QLDDS, the functionality of the [QuantLibAddin for C++](http://quantlib.org/quantlibaddin/index.html) interface may be distributed across multiple computers running different operating systems, in real-time.

This distribution is accomplished by publishing and subscribing to [DDS data type](DDSDataTypes.md) messages that trigger corresponding [QuantLibAddin for C++](http://quantlib.org/quantlibaddin/index.html) calls with the received data.

OpenDDS also allows to expose the functionality provided by [QuantLibAddin for C++](http://quantlib.org/quantlibaddin/index.html) to other languages including Java, C#, Python and Erlang.

![http://qldds.googlecode.com/git/misc/HighLevelDiagram.jpg](http://qldds.googlecode.com/git/misc/HighLevelDiagram.jpg)

## Features: ##

  * [DDS data type](DDSDataTypes.md) for QuantLibAddin for C++ 1.2.0
  * [Default Data Readers](DataReaders.md)
  * [Code generator](AutoGen.md) of DDS Data Types and Data Readers from QuantLibAddin for C++ XML
  * [Conversion functions between OpenDDS and QuantLib types](https://code.google.com/p/qldds/source/browse/qldds_utils/qldds_convert_utils.h)
  * [Convenience classes around OpenDDS and TAO APIs](Convenienceclasses.md)
  * Examples:
    1. [Interest Rate Swaps](ExampleIRS.md)
    1. [Swaptions](ExampleSwaptions.md)
    1. [EquityOptions](ExampleEquityOptions.md)


## Get Started: ##
### Prerequisites: ###
  * Perl - Required for OpenDDS
  * Python - Required for GenSrc, ObjectHandler and QuantLibAddin
  * GNU C++/Visual Studio 2008/Visual Studio 2010

> _See:_ [Configuring and Building QLDDS](ConfiguringAndBuilding.md)



[Latest Documentation](http://qldds.googlecode.com/git/QLDDS-doc.pdf)