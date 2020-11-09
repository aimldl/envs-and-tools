* Draft: 2020-05-28 (Thu)

# debconf-get-selections

**See also**: [debconf-set-selections](debconf-set-selections.md)

## Install `debconf-utils` package

```bash
$ sudo apt-get install debconf-utils
```

Run

```bash
$ sudo debconf-get-selections
```

The message related to Oracle is selected below.

```bash
$ sudo debconf-get-selections
# Oracle Technology Network License Agreement for Oracle Java SE
oracle-java14-installer	shared/present-oracle-license-v1-2	note	
  ...
# Location to the local file:
oracle-java14-installer	oracle-java14-installer/local	string	
  ...
# Do you accept the Oracle Technology Network License Agreement for Oracle Java SE terms?
oracle-java14-installer	shared/accepted-oracle-license-v1-2	boolean	true
  ...
# Declined "Oracle Technology Network License Agreement for Oracle Java SE"
oracle-java14-installer	shared/error-oracle-license-v1-2	error	
  ...
# File not found
oracle-java14-installer	oracle-java14-installer/not_exist	error	
  ...
$
```

The `grep` command can be used to filter out some messages as follows.

```bash
$ sudo debconf-get-selections | grep -i "oracle"
# Declined "Oracle Technology Network License Agreement for Oracle Java SE"
oracle-java14-installer	shared/error-oracle-license-v1-2	error	
# Do you accept the Oracle Technology Network License Agreement for Oracle Java SE terms?
oracle-java14-installer	shared/accepted-oracle-license-v1-2	boolean	true
# Oracle Technology Network License Agreement for Oracle Java SE
oracle-java14-installer	shared/present-oracle-license-v1-2	note	
oracle-java14-installer	oracle-java14-installer/not_exist	error	
oracle-java14-installer	oracle-java14-installer/local	string	
$
```

**See also**: [debconf-set-selections](debconf-set-selections.md)