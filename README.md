hotbot - Work in Progress
------

A very simple django app that tracks temperature and humidity data from an Arduino Uno.  It collects temperature and humidity and sends them back to a server API.  Its API is exposed by tastypie.


installation
------------

these instructions are optimized for running on a newly installed
Ubuntu 12.04 LTS host.

```
$ sudo apt-get install python-dev python-virtualenv libapache2-mod-wsgi
```

same for whichever db you want to use:

```
$ sudo apt-get install postgresql-9.1 postgresql-server-dev-9.1
[or]
$ sudo apt-get install mysql-server libmysqld-dev
[etc]
```

Install Git

```
$ sudo apt-get install git-core
```

create the database you'll use (pgsql example included, do equiv
for mysql):

```
% sudo su - postgres
(postgres)% psql
postgres=# create user MYUSERNAME with createdb password 'MYPASS';
CREATE ROLE
postgres=# \q
(postgres)% exit
% createdb -U MYUSERNAME MYDBNAME -W
Password: <'MYPASS'>
```

set up a directory to host the deployed code, and a deployment name
inside there (setting perms as needed):

```
$ mkdir -p /hotbot/tag_foo
$ cd /hotbot/tag_foo
```

get the code for this application, hotbot, from github, then check
out the tag to deploy:

```
$ git clone https://github.com/gwu-libraries/hotbot.git
$ cd hotbot
$ git checkout tag_foo
```

create and activate a virtualenv:

```
$ virtualenv --no-site-packages ENV
$ source ENV/bin/activate
```

install dependencies (note: based on db server choice, use psycopg2
or MySQL-python as appropriate):

```
$ pip install -r requirements.txt
```

copy over the local settings template to a real local settings file,
then add in correct ADMINS and DATABASE

```
$ cd hotbot/hotbot
$ cp local_settings.py.template local_settings.py
[edit edit edit]
```

arduino configuration
---------------------

Hardware: Arduino Uno R3, Arduino Ethernet Shield R3, DHT11 Temperature Sensor
Software: Arduino IDE (http://arduino.cc/en/main/software)

Copy and paste the Arduino sketch hotbot_arduino from hotbot/Arduino Code/ into the Arduino IDE sketchbook editor

Edit the following lines in the Arduino sketch to match your environment and preferred settings

Replace the 'AA 00 BB 11 CC 22' with the MAC address of your Ethernet shield, located on the bottom of the device
```
18 byte mac[] = {0xAA,0x00,0xBB,0x11,0xCC,0x22};
```
Replace the 'aa00bb11cc22' with the MAC address of your Ethernet shield, located on the bottom of the device
```
21 const char* MAC ="aa00bb11cc22";
```
Replace '0.0.0.0' with the IP address of the server that will receive your HTTP POST commands
```
24 byte server[]={0,0,0,0};
```
Replace '30' to define your posting interval, default 30 seconds
```
36 const unsigned long postingInterval = 30*1000;
```
Replace '0.0.0.0' with the IP address of the server that will receive your HTTP POST commands
```
94 client.println("Host: 0.0.0.0");
95 Serial.println("Host: 0.0.0.0");
```
Append your API key after 'sensor:'
```
104 client.println("Authorization: ApiKey sensor:");
105 Serial.println("Authorization: ApiKey sensor:");
```
Replace '0.0.0.0' with the IP address of the server that will receive your HTTP POST commands
```
151 client.println("Host: 0.0.0.0");
152 Serial.println("Host: 0.0.0.0");
```
Append your API key after 'sensor:'
```
161 client.println("Authorization: ApiKey sensor:");
162 Serial.println("Authorization: ApiKey sensor:");
```

Compile and Upload the sketch to your Arduino, launch the Arduino IDE Serial Monitor to debug your arduino sketch.  Check your apache logs to debug any HTTP errors.
