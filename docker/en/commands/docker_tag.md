* Rev.2: 2021-01-30 (Sat)
* Rev.1: 2020-03-12 (Thu)
* Draft: 2019-11-15 (Fri)

# docker tag

Create a tag TARGET_IMAGE that refers to SOURCE_IMAGE. 

```bash
$ docker tag SOURCE_IMAGE[:TAG] TARGET_IMAGE[:TAG]
```

This command names/renames a Docker image. It's like putting a sticky note on an image.

## Examples

Tag an image referenced by ID.

```bash
$ docker tag 0e5574283393 fedora/httpd:version1.0
```

Tag an image referenced by Name.

```bash
$ docker tag httpd fedora/httpd:version1.0
```

To tag a local image with name `httpd` and tag `test` into the `fedora` repository with `version1.0.test`:

```bash
$ docker tag httpd:test fedora/httpd:version1.0.test
```

Tag an image for a private repository.

```bash
$ docker tag 0e5574283393 myregistryhost:5000/fedora/httpd:version1.0
```

