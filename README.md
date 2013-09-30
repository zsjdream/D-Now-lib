D-Now-lib
=========

a set of libraries for msp430f5xxx

由于本人english is so-so，最近项目紧，为了节省时间，先用中文写啦，这个项目应该暂时还传播不到国际友人那里吧。

一套针对TI msp430f5xxx系列单片机的封装的库


====适用范围====

这套库是在msp430f5438/A上编写和测试的，没有在别的芯片上做过测试，不过TI的msp430f5xxx系列芯片模块基本都一样，只是模块数量有些不一样，所以理论上这套库完全适用于所有msp430f5xxx系列芯片，1，2，3，4系列芯片模块季春期地址可能不同，但是使用方法都一样，所以也有参考价值，但是可能不能直接使用。


====为什么叫D-Now====

D-Now有三层含义，Dream Now! Design Now! Develop Now!

旨在让对底层硬件不熟悉的人，能够更快的实现自己的想法，更快的设计产品，和更快的上手开发！


====为什么写这套库====

MSP430单片机（尤其是5438）从大二的时候开始接触，可以说是我接触的第二款也是最后一款MCU，第一款当然是51单片机啦，后来就转向DSP和ARM了，工作以后主要做Linux上的开发，Linux开发有个好处的驱动上层开发不需要关心底层驱动实现，所以我就萌生了一个想法，能做一套lib，让单片机开发也能更上层，让初学者不需要关心底层硬件接口和寄存器的操作，能更直观的提供一些接口，就像在windows或者linux这种有操作系统的平台上进行开发一样方便，所以就开始写这套lib。



====怎么写出这套库====

大三的时候曾经帮一个小公司设计过一套基于51的伺服控制系统，后来毕业后，那个老板请我帮忙把这套系统能迁移到更高级的单片机上，所以就想起了曾经参加TI杯用过的这个msp430f5438，说实话，当时参加比赛，代码都是拼凑的，也没有仔细的研究和看寄存器手册，弄懂每条语句的道理，在做了一年Linux内核开发以后，再去做单片机相关的东西，自然会更深入一些，借着这个机会，把5438的每一个模块寄存器手册都仔细的研究了一遍，基本上花了两个月的业余时间在研究5438手册，然后用了大概4个周末的时间把项目迁移到了5438上，接下来就着手开始了这套库的编写，先是从MCU自带的模块开始，串口，watchdog，timer，pwm等，然后开始封装一些常用的外围应用比如12864的LCD，温度传感器等，每个库差不多花两周时间（当然是业余时间啦），基本上是第一周进行编码实现，第二周进行优化，从寄存器的级别进行了优化，对接口反复的修改，以让初入单片机开发的同学们能更容易的上手和理解。



====为什么开源====

这套库已经写完有一年多了，一直躺在我的电脑里面，说实话，当时写的时候没想着要开源，一方面是想写好给学弟们免费用，只提供binary的库文件，一方面想搭配开发板卖，后来再三思考，中国人包括开发者，对软件的价值认可尚需时日，这不是靠我一个人的力量能改变的，所以，想依靠这套库来让开发板卖的比别人贵越想越不靠谱，再加上后来工作也比较忙，所以就没有继续写下去，除了把5438的一些片上模块封装好，外围的模块就写了个12864LCD，本来买了一堆传感器打算都封装好也没有继续做。
最近用到了不少github上的开源项目，就想到，既然花了那么多时间写的东西，就放上来，让有需要的朋友也免费用。




====配套项目====

除了开发这套库，我还开发了一个不错的bootloader和一个配套的PC上的烧写软件，利用这个bootloader，就可以通过串口来烧写程序，这样一来，可以省去购买编程器的钱（我上大三的时候买过一个当时500多块，现在大概200块左右），这个项目我后面也会放到github上免费让大家用。

其实，我当时对这个项目报很大的幻想，当时整个的想法是，再开发一个IDE，然后把这些库内置到IDE里面，IDE后续加入图形化编程，拖一个LCD进去，把IO用线连起来，代码就自动生成好了，然后在开发一些外围的模块，形成一个生态系统，当然这些想法后来由于各种各样的原因都没有实现。




====与Arduino生态====

看到这里，见多识广的小伙伴一定会问我，我上面想的那些东西不就是Arduino做的吗，对，其实，我当初做这东西的时候，根本不知道Arduino，所以我觉得我想的这个东西独一无二，今年7月份左右，有人跟我提这个，后来了解了一下才觉得，我当时想的那些东西，Arduino都已经做好了，有自己的IDE，自己的库，自己的生态圈。我一方面鄙视去年的自己孤陋寡闻，一方面又崇拜我自己有远见~--~，当然虽然有Arduino，但是Arduino毕竟是8bit单片机Arduino，不管从性能和功能都不能和5438来比，所以，我觉得我的这个东西还是有一些价值，至少，我在430单片机这边没有看到有类似的东西。




====开源策略====

就不提GPL这种慢性传染病了，大家随便用，心情好的话加个来源注释，当然欢迎commit欢迎fork。



====文档手册====

这套lib开发好就放着了，现在写文档确实还要花不少时间，不过，当时写的时候注释写的非常的详细，既然开源了，大家看代码，自己理解，非常容易，函数名字都很长，基本上就表达了这个函数的作用。当然，后面有时间我会补充文档。



====鸣谢===

雷二龙同学：帮忙设计了硬件，也对库的编写提了不少意见；

王建校老师：王建校是交大电气学院的，没有见过面，但是因为我买了他的书，在QQ上交流过不少，也给了不少好的建议。

每天9块9包邮网站：你懂得，哈哈，做个广告不过分吧，www.mt9k9.com

恒立仪表研究所：就是我前面说的大三找我帮忙设计控制系统的公司。

当然还有我目前供职的公司研华科技：正是由于公司不像某些没人性公司一样需要周末加班，才使得我有业余时间来做这个。




====联系我====

有任何问题请发信到zsj@itwlw.com,我会及时回复，短期内我也没有时间再去开发新的功能，封装新的模块，所以更新的动力就是大家有问题给我提，我尽我努力来解决和修复，然后再去更新，功能上欢迎大家一起补充。

