<h1>EasyNetwork框架简介</h1>


<br><br><br>
<b>EasyNetwork</b> 是一个基于linux的C/C++服务器开发框架。其对网络层(如socket、IO多路复用等)、链接的创建和接收、协议数据的序列化和反序列化、以及数据的发送和接收进行了封装，为应用层提供了统一的调用接口，从而为服务端的开发提供了快速高效的方法。同时框架提供了如单线程服务器、多线程服务器、线程池等常见的服务器端开发范式，通过框架提供的enetlib工具，开发者可以快速生成相应的服务器框架类代码。EasyNetwork框架使得开发者从底层的网络编程细节中解脱出来，从而能够把精力集中于业务逻辑层的开发。更多的说明见 <a href='FQA.md'>FQA</a> 。<br>
<br>
<br>
每个服务器都是 <i>NetInterface</i> 的一个实例。 <i>NetInterface</i> 为应用层提供了接收和发送协议等接口，应用层通过实现这些接口对协议进行处理便可完成自己的业务逻辑。开发者可以不用关心链接的创建、接收和管理、数据的接收、序列化合反序列化等底层的工作，这些都由 <i>NetInterface</i> 完成。另外，框架提供的 <i>ConnectThread</i> 类和 <i>ConnectThreadPool</i> 类对多线程服务器开发范式进行了封装。 <i>ConnectThread</i> 也是 <i>NetInterface</i> 的一个实例。当收到新的链接请求时，框架按某种策略自动把新的链接分配到 <i>ConnectThread</i> ，由 <i>ConnectThread</i> 进行处理。这里是 <a href='MainFramework.md'>框架详细介绍</a> 。<br>
<br>
<br>
最新的框架源码可以从这里下载： <a href='http://easynetwork.googlecode.com/files/libnetframework_20130121.tar'>libnetframework_20130121.tar</a> 。这里可以找到其他 <a href='download.md'>旧版本</a> 。<br>
<br>
<br>
框架的使用和例子可以参考：<br>
<ol><li><a href='enetlib.md'>利用enetlib自动化生成框架类代码</a>
</li><li><a href='samples.md'>1分钟搭建服务器框架</a>
</li><li><a href='MThreadDownload.md'>多任务、多线程下载服务器</a></li></ol>


<br><br><br>
另外，框架使用 <a href='libslog.md'>libslog</a> 日志文件系统。<br>
<br>
<br><br><br>
任何宝贵的意见和建议请联系作者：<i>xmulyj@gmail.com</i>

<br><br>