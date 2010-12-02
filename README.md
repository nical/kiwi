<h1> Kiwi </h1>

A generic and easy to use node compositor library for C++. 


<img src='http://img808.imageshack.us/img808/4377/kiwiboxespng01.png' border='0'/>

Checkout the [wiki](http://github.com/nical/kiwi/wiki) !<br/>
And also the doxygen [class documentation](http://nical.github.com/kiwi/doc/doxygen/html/annotated.html).

<h2> Containers and filters </h2>

Kiwi features a powerful pipeline system composed of resources and filters : 
<ul>
	<li>A <b>container</b> (kiwi::core::Container) is an object that holds data and give access to the it by providing readers and writers ports (mostly output ports).</li>
	<li>A <b>Filter</b> (kiwi::core::Filter) is a resource that can be executed using its process() method. Filters inherit from resources their connecting system. </li>
	<li>A <b>Pipeline</b> (kiwi::core::Pipeline) is a filter that contains other filters (including eventually pipelines) and is responsible for processing each of its filters in the correct order. This is the composite design pattern applied to the kiwi system. </li>
</ul>

Kiwi is designed to make the creation of Resources and Filters very easy. Just create a class deriving from kiwi::core::Resource or kiwi::core::Filter and overload a few methods.

<h2> The project's advancement </h2>

kiwi 0.2.2

Kiwi is still at an early stage, and interfaces are subject to change.

<h3> Implemented </h3>
 - The Node base class with all the connection system
 - Filter and Container base classes 
 - Some generic Containers (ArrayContainer, MultiArrayContainer, cairo::ImageContainer, Value ...)

<h3> Currently in development </h3>
 - Pipeline classes
 - Imaging filters using cairo

<h3> TODO </h3>
What kiwi actually needs:
<ul>
 <li> Pipeline classes. </li>
 <li> A set of resources and filters to demonstrate kiwi's potential ! </li>
 <li> A frontend to connect graphically kiwi boxes and see the result in live. </li>
 <li> Better automated unit tests with reports (right now it's a huge load of use cases with tons of assert(..) everywhere...)
</ul> 

<h2> License </h2>

Most of Kiwi's source code is under the <b>new BSD License</b>. However some of the plugin sets 
are under other licenses, like the image::cairo plugin set that is under the LGPL. See the
readme.txt file in each sub-project directory for informations about which license applies.

<h2> Project member(s) </h2>

For now the Kiwi project is designed/developed/maintained by <b>Nicolas Silva</b>.

I would be very happy to share this experience with anyone who is motivated to create and/or test filters and resources based on kiwi!

To contact me:

email: nical.silva@gmail.com <br/>
twitter: [@nicalsilva](http://twitter.com/#!/nicalsilva)<br/>
my resume [(fr)](http://github.com/nical/resume/raw/master/fr/NicolasSilva.pdf)<br/>

Recently Thibaut Vuillemin (@semprobe) joined the project as a developer !
