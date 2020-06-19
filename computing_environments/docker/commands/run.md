run.md

Docker run options

Other Docker infos

--network=host
using the host’s networking stack (i.e. the container and the host are identical in their network usage, so port XX in the container is port XX on the host.)

NETWORK: HOST
With the network set to host a container will share the host’s network stack and all interfaces from the host will be available to the container. The container’s hostname will match the hostname on the host system. Note that --mac-address is invalid in host netmode. Even in host network mode a container has its own UTS namespace by default. As such --hostname is allowed in host network mode and will only change the hostname inside the container. Similar to --hostname, the --add-host, --dns, --dns-search, and --dns-option options can be used in host network mode. These options update /etc/hosts or /etc/resolv.conf inside the container. No change are made to /etc/hosts and /etc/resolv.conf on the host.

Compared to the default bridge mode, the host mode gives significantly better networking performance since it uses the host’s native networking stack whereas the bridge has to go through one level of virtualization through the docker daemon. It is recommended to run containers in this mode when their networking performance is critical, for example, a production Load Balancer or a High Performance Web Server.

-w --workdir=/app
