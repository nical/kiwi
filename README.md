<h1> Kiwi </h1>

A generic and easy to use pipeline system. 


<img src='http://img808.imageshack.us/img808/4377/kiwiboxespng01.png' border='0'/>


<h2> Resources and filters </h2>

Kiwi features a powerful pipeline system composed of resources and filters : 
<ul>
	<li>A <b>resource</b> (kiwi::core::Resource) is an object that contains input and output ports and give access to the data it contains by providing readers and writers throught these ports.</li>
	<li>A <b>Filter</b> (kiwi::core::Filter) is a resource that can be executed using its process() method. Filters inherit from resources their connecting system. </li>
	<li>A <b>Pipeline</b> (kiwi::core::Pipeline) is a filter that contains other filters (including eventually pipelines) and is responsible for processing each of its filters in the correct order. This is the composite design pattern applied to the kiwi system. </li>
</ul>

<h2> Creating new resources and filters </h2>

Kiwi is designed to make the creation of Resources and Filters very easy. Just create a class deriving from kiwi::core::Resource or kiwi::core::Filter and overload a few methods.

<h3> Resources </h3>

This page is in under construction, more informations are to come soon

<h3> Filters </h3>

This page is in under construction, more informations are to come soon

<h2> The project's advancement </h2>

kiwi 0.2.2

Kiwi is still at an early stage, and interfaces are subject to change.

<h3> Implemented </h3>
 - Resource base class with all the connection systeme
 - Filter base class 

<h3> Currently in developement </h3>
 - The generic ArrayData Resource
 - A simple string container

<h3> TODO </h3>
<ul>
 <li> Pipeline classes. </li>
 <li> A set of resources and filters to demonstrate kiwi's potential ! </li>
 <li> A web-based frontend (html+svg+js) to connect graphically kiwi boxes and see the result in live. </li>
</ul> 

<h2> License </h2>

Most of Kiwi's source code is under the <b>new BSD License</b>. However some of the plugin sets 
are under other licenses, like the image::cairo plugin set that is under the LGPL. See the
readme.txt file in each sub-project directory for informations about which license apply.

<h2> Project member(s) </h2>

For know the Kiwi project is designed/developed/maintained by <b>Nicolas Silva</b>.

I would be very happy to share this experience with anyone who is motivated to create and/or test filters and resources based on kiwi!

To contact me:

email: nical.silva@gmail.com <br/>
twitter: [@nicalsilva](http://twitter.com/#!/nicalsilva)

