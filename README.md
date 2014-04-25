hotbot
-------

a very simple django app that tracks temperature and humidity data from an Arduino Uno.  it collects temperature and humidity and sends them back to a server API.  its API is exposed by tastypie.


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
