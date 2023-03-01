### QFutureInterfaceTest
#### QFuture相关类的介绍
-   QFuture：表示异步计算的结果
-   QFutureWatcher：QFuture本身不带信号槽，可使用QFutureWatcher进行监控
-   QFutureInterface：该类没有提供文档，出现于Qt源码。QFuture与QFutureInterface的关系类似std::future与std::promise（Qt6中基于QFutureInterface封装了一个QPromise类）。QFutureInterface可用于生成QFuture，在Qt类实现中，QFuture持有一个QFutureInterface成员。

&nbsp; 
#### 说明
该demo演示了QFuture和QFutureInterfaceTest的用法；
