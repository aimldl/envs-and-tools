2020-0325 (Wed)

> !SESSION 2020-03-25 11:48:30.636 -----------------------------------------------
> eclipse.buildId=R3.7.9.201912052356
> java.version=12.0.2
> java.vendor=Oracle Corporation
> BootLoader constants: OS=linux, ARCH=x86_64, WS=gtk, NL=ko_KR
> Framework arguments:  /opt/xmind-8-update9-linux/XMind_amd64/configuration ./configuration -eclipse.keyring @user.home/.xmind/secure_storage_linux
> Command-line arguments:  -os linux -ws gtk -arch x86_64 /opt/xmind-8-update9-linux/XMind_amd64/configuration ./configuration -data /home/aimldl/workspace -eclipse.keyring @user.home/.xmind/secure_storage_linux
>
> !ENTRY org.eclipse.osgi 4 0 2020-03-25 11:48:31.090
> !MESSAGE Application error
> !STACK 1
> java.lang.IllegalStateException: Unable to acquire application service. Ensure that the org.eclipse.core.runtime bundle is resolved and started (see config.ini).
> 	at org.eclipse.core.runtime.internal.adaptor.EclipseAppLauncher.start(EclipseAppLauncher.java:78)
> 	at org.eclipse.core.runtime.adaptor.EclipseStarter.run(EclipseStarter.java:388)
> 	at org.eclipse.core.runtime.adaptor.EclipseStarter.run(EclipseStarter.java:243)
> 	at java.base/jdk.internal.reflect.NativeMethodAccessorImpl.invoke0(Native Method)
> 	at java.base/jdk.internal.reflect.NativeMethodAccessorImpl.invoke(NativeMethodAccessorImpl.java:62)
> 	at java.base/jdk.internal.reflect.DelegatingMethodAccessorImpl.invoke(DelegatingMethodAccessorImpl.java:43)
> 	at java.base/java.lang.reflect.Method.invoke(Method.java:567)
> 	at org.eclipse.equinox.launcher.Main.invokeFramework(Main.java:673)
> 	at org.eclipse.equinox.launcher.Main.basicRun(Main.java:610)
> 	at org.eclipse.equinox.launcher.Main.run(Main.java:1519)
> 	at org.eclipse.equinox.launcher.Main.main(Main.java:1492)







/opt/xmind-8-update9-linux/plugins$ ls -al org.eclipse.equinox.launcher.gtk.linux.x86_64
org.eclipse.equinox.launcher.gtk.linux.x86_64.nl_ar_4.5.0.v20150804081228.jar
org.eclipse.equinox.launcher.gtk.linux.x86_64.nl_da_4.5.0.v20150804081228.jar
org.eclipse.equinox.launcher.gtk.linux.x86_64.nl_de_4.5.0.v20150804081228.jar
org.eclipse.equinox.launcher.gtk.linux.x86_64.nl_es_4.5.0.v20150804081228.jar
org.eclipse.equinox.launcher.gtk.linux.x86_64.nl_fr_4.5.0.v20150804081228.jar
org.eclipse.equinox.launcher.gtk.linux.x86_64.nl_it_4.5.0.v20150804081228.jar
org.eclipse.equinox.launcher.gtk.linux.x86_64.nl_ja_4.5.0.v20150804081228.jar
org.eclipse.equinox.launcher.gtk.linux.x86_64.nl_ko_4.5.0.v20150804081228.jar
org.eclipse.equinox.launcher.gtk.linux.x86_64.nl_pt_BR_4.5.0.v20150804081228.jar
org.eclipse.equinox.launcher.gtk.linux.x86_64.nl_ru_4.5.0.v20150804081228.jar
org.eclipse.equinox.launcher.gtk.linux.x86_64.nl_zh_4.5.0.v20150804081228.jar
org.eclipse.equinox.launcher.gtk.linux.x86_64.nl_zh_TW_4.5.0.v20150804081228.jar
org.eclipse.equinox.launcher.gtk.linux.x86_64_1.1.400.v20160518-1444/



다른 에러. This is a common error! I feel lucky.





It seems XMind doesn't work with later versions of JVM, it needs Java 8 but can't run with the `--add-modules` option since it was introduced in later versions.



This is how I managed to make it run again:

- Step 1: Select the java-8-openjdk option using the command `sudo update-alternatives --config java`

Google search: How To Install Java with `apt` on Ubuntu 18.04

[How To Install Java with `apt` on Ubuntu 18.04](https://www.digitalocean.com/community/tutorials/how-to-install-java-with-apt-on-ubuntu-18-04)

```
apt install default-jre
apt install openjdk-11-jre-headless
apt install openjdk-8-jre-headless
apt install openjdk-9-jre-headless
```

(base) aimldl@Home-Laptop:~/.xmind$ sudo apt install openjdk-8-
openjdk-8-dbg           openjdk-8-jdk           openjdk-8-jre-dcevm     openjdk-8-source
openjdk-8-demo          openjdk-8-jdk-headless  openjdk-8-jre-headless  
openjdk-8-doc           openjdk-8-jre           openjdk-8-jre-zero      
(base) aimldl@Home-Laptop:~/.xmind$ sudo apt install openjdk-8-jdk







$ sudo update-alternatives --config java
대체 항목 java에 대해 (/usr/bin/java 제공) 1개 선택이 있습니다.

  선택       경로                                우선순� 상태
------------------------------------------------------------
  0            /usr/lib/jvm/java-12-oracle/bin/java   1091      자동 모드
* 1            /usr/lib/jvm/java-12-oracle/bin/java   1091      수동 모드

Press <enter> to keep the current choice[*], or type selection number: 



(base) aimldl@Home-Laptop:~/.xmind$ java -version
java version "12.0.2" 2019-07-16
Java(TM) SE Runtime Environment (build 12.0.2+10)
Java HotSpot(TM) 64-Bit Server VM (build 12.0.2+10, mixed mode, sharing)
(base) aimldl@Home-Laptop:~/.xmind$ sudo update-alternatives --config java
대체 항목 java에 대해 (/usr/bin/java 제공) 2개 선택이 있습니다.

  선택       경로                                          우선순� 상태
------------------------------------------------------------
  0            /usr/lib/jvm/java-12-oracle/bin/java             1091      자동 모드
* 1            /usr/lib/jvm/java-12-oracle/bin/java             1091      수동 모드
  2            /usr/lib/jvm/java-8-openjdk-amd64/jre/bin/java   1081      수동 모드

Press <enter> to keep the current choice[*], or type selection number: 2
update-alternatives: using /usr/lib/jvm/java-8-openjdk-amd64/jre/bin/java to provide /usr/bin/java (java) in manual mode
(base) aimldl@Home-Laptop:~/.xmind$ java -version
openjdk version "1.8.0_242"
OpenJDK Runtime Environment (build 1.8.0_242-8u242-b08-0ubuntu3~18.04-b08)
OpenJDK 64-Bit Server VM (build 25.242-b08, mixed mode)





- Step 2: the earlier fix to the .ini file consisted in adding this line at the end of the file `--add-modules=ALL-SYSTEM`. Remove this line.
- Step 3: Relaunch the XMind program and it should work.

It seems XMind doesn't work with later versions of JVM, it needs Java 8 but can't run with the `--add-modules` option since it was introduced in later versions.

[[XMind 8 suddenly stopped working on Ubuntu 18.04 LTS after .ini fix](https://askubuntu.com/questions/1138225/xmind-8-suddenly-stopped-working-on-ubuntu-18-04-lts-after-ini-fix)](https://askubuntu.com/questions/1138225/xmind-8-suddenly-stopped-working-on-ubuntu-18-04-lts-after-ini-fix)



!SESSION 2020-03-25 18:25:40.903 -----------------------------------------------
eclipse.buildId=R3.7.8.201807240049
java.version=12.0.2
java.vendor=Oracle Corporation
BootLoader constants: OS=linux, ARCH=x86_64, WS=gtk, NL=ko_KR
Framework arguments:  -eclipse.keyring @user.home/.xmind/secure_storage_linux
Command-line arguments:  -os linux -ws gtk -arch x86_64 -data /opt/xmind/workspace -eclipse.keyring @user.home/.xmind/secure_storage_linux

!ENTRY org.xmind.cathy 1 0 2020-03-25 18:25:46.947
!MESSAGE Skip unrecognized command line argument: '-eclipse.keyring'

!ENTRY org.xmind.cathy 1 0 2020-03-25 18:25:46.947
!MESSAGE Skip unrecognized command line argument: '@user.home/.xmind/secure_storage_linux'

!ENTRY org.eclipse.osgi.compatibility.state.nl_sl 2 0 2020-03-25 18:25:47.006
!MESSAGE Could not resolve module: org.eclipse.osgi.compatibility.state.nl_sl [849]
  Unresolved requirement: Fragment-Host: org.eclipse.osgi.compatibility.state
  Unresolved requirement: Fragment-Host: org.eclipse.osgi.compatibility.state


!ENTRY org.eclipse.osgi.compatibility.state.nl_ko 2 0 2020-03-25 18:25:47.006
!MESSAGE Could not resolve module: org.eclipse.osgi.compatibility.state.nl_ko [846]
  Unresolved requirement: Fragment-Host: org.eclipse.osgi.compatibility.state
  Unresolved requirement: Fragment-Host: org.eclipse.osgi.compatibility.state


!ENTRY org.eclipse.osgi.compatibility.state.nl_es 2 0 2020-03-25 18:25:47.006
!MESSAGE Could not resolve module: org.eclipse.osgi.compatibility.state.nl_es [842]
  Unresolved requirement: Fragment-Host: org.eclipse.osgi.compatibility.state
  Unresolved requirement: Fragment-Host: org.eclipse.osgi.compatibility.state


!ENTRY org.eclipse.osgi.compatibility.state.nl_ar 2 0 2020-03-25 18:25:47.006
!MESSAGE Could not resolve module: org.eclipse.osgi.compatibility.state.nl_ar [839]
  Unresolved requirement: Fragment-Host: org.eclipse.osgi.compatibility.state
  Unresolved requirement: Fragment-Host: org.eclipse.osgi.compatibility.state


!ENTRY org.eclipse.osgi.compatibility.state.nl_zh 2 0 2020-03-25 18:25:47.006
!MESSAGE Could not resolve module: org.eclipse.osgi.compatibility.state.nl_zh [850]
  Unresolved requirement: Fragment-Host: org.eclipse.osgi.compatibility.state
  Unresolved requirement: Fragment-Host: org.eclipse.osgi.compatibility.state


!ENTRY org.eclipse.osgi.compatibility.state.nl_de 2 0 2020-03-25 18:25:47.006
!MESSAGE Could not resolve module: org.eclipse.osgi.compatibility.state.nl_de [841]
  Unresolved requirement: Fragment-Host: org.eclipse.osgi.compatibility.state
  Unresolved requirement: Fragment-Host: org.eclipse.osgi.compatibility.state


!ENTRY org.eclipse.osgi.compatibility.state.nl_fr 2 0 2020-03-25 18:25:47.006
!MESSAGE Could not resolve module: org.eclipse.osgi.compatibility.state.nl_fr [843]
  Unresolved requirement: Fragment-Host: org.eclipse.osgi.compatibility.state
  Unresolved requirement: Fragment-Host: org.eclipse.osgi.compatibility.state


!ENTRY org.eclipse.osgi.compatibility.state.nl_ru 2 0 2020-03-25 18:25:47.007
!MESSAGE Could not resolve module: org.eclipse.osgi.compatibility.state.nl_ru [848]
  Unresolved requirement: Fragment-Host: org.eclipse.osgi.compatibility.state
  Unresolved requirement: Fragment-Host: org.eclipse.osgi.compatibility.state


!ENTRY org.eclipse.osgi.compatibility.state.nl_zh_TW 2 0 2020-03-25 18:25:47.007
!MESSAGE Could not resolve module: org.eclipse.osgi.compatibility.state.nl_zh_TW [851]
  Unresolved requirement: Fragment-Host: org.eclipse.osgi.compatibility.state
  Unresolved requirement: Fragment-Host: org.eclipse.osgi.compatibility.state


!ENTRY org.eclipse.osgi.compatibility.state.nl_it 2 0 2020-03-25 18:25:47.007
!MESSAGE Could not resolve module: org.eclipse.osgi.compatibility.state.nl_it [844]
  Unresolved requirement: Fragment-Host: org.eclipse.osgi.compatibility.state
  Unresolved requirement: Fragment-Host: org.eclipse.osgi.compatibility.state


!ENTRY org.eclipse.osgi.compatibility.state.nl_pt_BR 2 0 2020-03-25 18:25:47.007
!MESSAGE Could not resolve module: org.eclipse.osgi.compatibility.state.nl_pt_BR [847]
  Unresolved requirement: Fragment-Host: org.eclipse.osgi.compatibility.state
  Unresolved requirement: Fragment-Host: org.eclipse.osgi.compatibility.state


!ENTRY org.eclipse.osgi.compatibility.state.nl_ja 2 0 2020-03-25 18:25:47.007
!MESSAGE Could not resolve module: org.eclipse.osgi.compatibility.state.nl_ja [845]
  Unresolved requirement: Fragment-Host: org.eclipse.osgi.compatibility.state
  Unresolved requirement: Fragment-Host: org.eclipse.osgi.compatibility.state


!ENTRY org.eclipse.osgi.compatibility.state.nl_da 2 0 2020-03-25 18:25:47.007
!MESSAGE Could not resolve module: org.eclipse.osgi.compatibility.state.nl_da [840]
  Unresolved requirement: Fragment-Host: org.eclipse.osgi.compatibility.state
  Unresolved requirement: Fragment-Host: org.eclipse.osgi.compatibility.state


!ENTRY org.eclipse.osgi 4 0 2020-03-25 18:25:47.008
!MESSAGE 응용프로그램 오류
!STACK 1
org.eclipse.e4.core.di.InjectionException: java.lang.NoClassDefFoundError: javax/annotation/PostConstruct
	at org.eclipse.e4.core.internal.di.InjectorImpl.internalMake(InjectorImpl.java:386)
	at org.eclipse.e4.core.internal.di.InjectorImpl.make(InjectorImpl.java:294)
	at org.eclipse.e4.core.contexts.ContextInjectionFactory.make(ContextInjectionFactory.java:162)
	at org.eclipse.e4.ui.internal.workbench.swt.E4Application.createDefaultHeadlessContext(E4Application.java:490)
	at org.eclipse.e4.ui.internal.workbench.swt.E4Application.createDefaultContext(E4Application.java:504)
	at org.eclipse.e4.ui.internal.workbench.swt.E4Application.createE4Workbench(E4Application.java:203)
	at org.eclipse.ui.internal.Workbench$5.run(Workbench.java:626)
	at org.eclipse.core.databinding.observable.Realm.runWithDefault(Realm.java:336)
	at org.eclipse.ui.internal.Workbench.createAndRunWorkbench(Workbench.java:604)
	at org.eclipse.ui.PlatformUI.createAndRunWorkbench(PlatformUI.java:148)
	at org.xmind.cathy.internal.CathyApplication.start(CathyApplication.java:137)
	at org.eclipse.equinox.internal.app.EclipseAppHandle.run(EclipseAppHandle.java:196)
	at org.eclipse.core.runtime.internal.adaptor.EclipseAppLauncher.runApplication(EclipseAppLauncher.java:134)
	at org.eclipse.core.runtime.internal.adaptor.EclipseAppLauncher.start(EclipseAppLauncher.java:104)
	at org.eclipse.core.runtime.adaptor.EclipseStarter.run(EclipseStarter.java:388)
	at org.eclipse.core.runtime.adaptor.EclipseStarter.run(EclipseStarter.java:243)
	at java.base/jdk.internal.reflect.NativeMethodAccessorImpl.invoke0(Native Method)
	at java.base/jdk.internal.reflect.NativeMethodAccessorImpl.invoke(NativeMethodAccessorImpl.java:62)
	at java.base/jdk.internal.reflect.DelegatingMethodAccessorImpl.invoke(DelegatingMethodAccessorImpl.java:43)
	at java.base/java.lang.reflect.Method.invoke(Method.java:567)
	at org.eclipse.equinox.launcher.Main.invokeFramework(Main.java:673)
	at org.eclipse.equinox.launcher.Main.basicRun(Main.java:610)
	at org.eclipse.equinox.launcher.Main.run(Main.java:1519)
	at org.eclipse.equinox.launcher.Main.main(Main.java:1492)
Caused by: java.lang.NoClassDefFoundError: javax/annotation/PostConstruct
	at org.eclipse.e4.core.internal.di.InjectorImpl.inject(InjectorImpl.java:151)
	at org.eclipse.e4.core.internal.di.InjectorImpl.internalMake(InjectorImpl.java:375)
	... 23 more
Caused by: java.lang.ClassNotFoundException: javax.annotation.PostConstruct cannot be found by org.eclipse.e4.core.di_1.6.0.v20160319-0612
	at org.eclipse.osgi.internal.loader.BundleLoader.findClassInternal(BundleLoader.java:398)
	at org.eclipse.osgi.internal.loader.BundleLoader.findClass(BundleLoader.java:361)
	at org.eclipse.osgi.internal.loader.BundleLoader.findClass(BundleLoader.java:353)
	at org.eclipse.osgi.internal.loader.ModuleClassLoader.loadClass(ModuleClassLoader.java:161)
	at java.base/java.lang.ClassLoader.loadClass(ClassLoader.java:521)
	... 25 more

!ENTRY org.eclipse.e4.ui.workbench 4 0 2020-03-25 18:25:47.015
!MESSAGE FrameworkEvent ERROR
!STACK 0
java.lang.NoClassDefFoundError: javax/annotation/PreDestroy
	at org.eclipse.e4.core.internal.di.InjectorImpl.disposed(InjectorImpl.java:426)
	at org.eclipse.e4.core.internal.di.Requestor.disposed(Requestor.java:154)
	at org.eclipse.e4.core.internal.contexts.ContextObjectSupplier$ContextInjectionListener.update(ContextObjectSupplier.java:78)
	at org.eclipse.e4.core.internal.contexts.TrackableComputationExt.update(TrackableComputationExt.java:111)
	at org.eclipse.e4.core.internal.contexts.TrackableComputationExt.handleInvalid(TrackableComputationExt.java:74)
	at org.eclipse.e4.core.internal.contexts.EclipseContext.dispose(EclipseContext.java:176)
	at org.eclipse.e4.core.internal.contexts.osgi.EclipseContextOSGi.dispose(EclipseContextOSGi.java:106)
	at org.eclipse.e4.core.internal.contexts.osgi.EclipseContextOSGi.bundleChanged(EclipseContextOSGi.java:139)
	at org.eclipse.osgi.internal.framework.BundleContextImpl.dispatchEvent(BundleContextImpl.java:903)
	at org.eclipse.osgi.framework.eventmgr.EventManager.dispatchEvent(EventManager.java:230)
	at org.eclipse.osgi.framework.eventmgr.ListenerQueue.dispatchEventSynchronous(ListenerQueue.java:148)
	at org.eclipse.osgi.internal.framework.EquinoxEventPublisher.publishBundleEventPrivileged(EquinoxEventPublisher.java:213)
	at org.eclipse.osgi.internal.framework.EquinoxEventPublisher.publishBundleEvent(EquinoxEventPublisher.java:120)
	at org.eclipse.osgi.internal.framework.EquinoxEventPublisher.publishBundleEvent(EquinoxEventPublisher.java:112)
	at org.eclipse.osgi.internal.framework.EquinoxContainerAdaptor.publishModuleEvent(EquinoxContainerAdaptor.java:156)
	at org.eclipse.osgi.container.Module.publishEvent(Module.java:476)
	at org.eclipse.osgi.container.Module.doStop(Module.java:634)
	at org.eclipse.osgi.container.Module.stop(Module.java:498)
	at org.eclipse.osgi.container.SystemModule.stop(SystemModule.java:191)
	at org.eclipse.osgi.internal.framework.EquinoxBundle$SystemBundle$EquinoxSystemModule$1.run(EquinoxBundle.java:165)
	at java.base/java.lang.Thread.run(Thread.java:835)
Caused by: java.lang.ClassNotFoundException: javax.annotation.PreDestroy cannot be found by org.eclipse.e4.core.di_1.6.0.v20160319-0612
	at org.eclipse.osgi.internal.loader.BundleLoader.findClassInternal(BundleLoader.java:398)
	at org.eclipse.osgi.internal.loader.BundleLoader.findClass(BundleLoader.java:361)
	at org.eclipse.osgi.internal.loader.BundleLoader.findClass(BundleLoader.java:353)
	at org.eclipse.osgi.internal.loader.ModuleClassLoader.loadClass(ModuleClassLoader.java:161)
	at java.base/java.lang.ClassLoader.loadClass(ClassLoader.java:521)
	... 21 more



!ENTRY org.xmind.cathy 1 0 2020-03-25 18:25:46.947
!MESSAGE Skip unrecognized command line argument: '-eclipse.keyring'

!ENTRY org.xmind.cathy 1 0 2020-03-25 18:25:46.947
!MESSAGE Skip unrecognized command line argument: '@user.home/.xmind/secure_storage_linux'



TODO 

post my solution to 

https://www.danieblog.com/technology/software/error-unable-to-start-xmind-in-linux-67.html

xmind !MESSAGE Skip unrecognized command line argument: '-eclipse.keyring'