<h2> Repository Introduction </h2>
This repository consists two independent projects:

1. An android application equipped with GCM for ease of message passing, both from client to an android device and from android device to client.
2. K-means clustering algorithm, used in AI as a preprocessing step when studying data, written both a serial implementation and parallel implementation in C++.

This google docs holds my journal entries: https://docs.google.com/document/d/1Hsu98IuVjZeFKfnE8tJSRsaLk8vzZTY3kN5t7iKRFHw/edit?usp=sharing

<h2> Platform Task (GCM) </h2>
<h3> Task Introduction </h3>
The goal of the first task was to create an android application with bidirectional message passing capabilities using the provided Google frame work GCM (Google Cloud Messaging). 

GCM consists of three main components:

1. **Application server**: Used to send or receive messages from GCM server.
2. **GCM server**: Acts as a mediatory server between the client application and the application server, handles messaging queuing, and transfer of messages.
3. **Client application**: Used to send or receive messages from the GCM server (in this case it was an android application, running on lollipop).

<h3> Compilation Instructions </h3>
1.	Import PlatformTask(GCM) into android studio and make sure all the dependences for client application are met
2.	Go to https://developers.google.com/mobile/add?platform=android&cntapi=gcm&cnturl=https:%2F%2Fdevelopers.google.com%2Fcloud-messaging%2Fandroid%2Fclient&cntlbl=Continue%20Adding%20GCM%20Support&%3Fconfigured%3Dtrue and generate
3.	Fill in App name: GCMImplementation and android package name: com.example.rooshan.gcmimplementation
4.	Select enable GCM (check box) for my application and hit next where you will be asked to ‘Continue to generate configuration files ->’, click generate and download the google-services.json
5.	Move google-services.json into the root directory of the client application which is located where you saved the extracted Client Application folder/app/ in that directory. For example if your Client Application is in downloads you would put the google-services.json into ~/Download/Client/\ Application.
6.	Next build the application using android studio and run the application (either on your android phone or the build in simulator in android studio).

<h3> Task Dependences </h3>
* Andriod Studio >= 1.5.1
* Gradle >= 1.5.0
* gms:google-services >= 8.4.0
* appcompat >= v7:23.1.1
* jdk >= 1.8.0_66
* Compile-SDK-Version = Andriod 6.0 (Marshmallow)  - Android 4.0.3 (Icecream Sandwich)
