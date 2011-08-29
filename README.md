<h1> Kiwi </h1>

A generic and easy to use node compositor library for D2 and C++. 


<img src='http://img808.imageshack.us/img808/4377/kiwiboxespng01.png' border='0'/>

Checkout the [wiki](http://github.com/nical/kiwi/wiki) !<br/>
Doxygen qnd ddoc documentation will be available soon.

<h2> Main concepts
A kiwi node compositor contains nodes that are linked through their input and output ports. output ports hold Data objects which can be any kind of data structure. Data objects can be composite (for instance a RGBA image container can be described as 4 Read+Zrite color buffer containers and two read only integer containers exposing the width and heigh of the image9, in which case the corresponding output ports become composite as well, and their subPorts follow the same structure as the Data object.
Ports can be used to emit data or just signals, which means that Kiwi can be used for processing workflows as well as visual scripting, or even just use it for contentent generation (like shaders) using introspection on the node graph.
The backend is not dependent to any frontend, though optional Qt based widgets will be developed.  

<h2> The project's advancement (D) </h2>

Kiwi is still at an early stage, and interfaces are subject to change.
Right now the library is mostly developed in D, and the C++ port will follow. There are old versions of the C++ implementation available in this repository's history, but they dont reflect the architecture of the current version of the library.

<h3> Implemented </h3>
 - The core interfaces and the port connection system.
 - The "dynamic" backend implementing the core interfaces for nodes and ports.
 - Runtime data type descriptor and manager.  
<h3> Currently in development </h3>
 - Node groups (dynamic backend)
 - Generic graph algorithms to help with node management, ordonnancing, etc.


<h3> TODO </h3>
 - C++ port of the core API and dynamic backend.
 - Script integration (starting with Lua) to expose the library to the script and also make serializable nodes running lua code.
 - Network layer to allow remote manipulation of nodes (in a separate and optional library).
 - Qt widgets as an optional frontend.
 - Fun nodes to show kiwi's featues.
 - Experiment shader generators, and visual scripting using kiwi.
<h2> License </h2>

Kiwi's source code is under the <b>new BSD License</b> or the <b>Lesser Gnu Public License</b>. 

<h2> Project member(s) </h2>

For now the Kiwi project is designed/developed/maintained by <b>Nicolas Silva</b>.

I would be very happy to share this experience with anyone willing to contribute!
To contact me:

email: nical.silva@gmail.com <br/>
twitter: [@nicalsilva](http://twitter.com/#!/nicalsilva)<br/>
my resume [(fr)](http://github.com/nical/resume/raw/master/fr/NicolasSilva.pdf)<br/>
