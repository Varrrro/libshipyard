# Shipyard task deployment library

This C library is used by tasks that are to be orchestrated with the Shipyard
system. For more information about Shipyard, please see [the server's
repository](https://github.com/Varrrro/shipyard-server).

## Usage

Although it's a normal C library, it is not meant to be used like one. At least
not fully. The library is packaged as a Docker image which tasks' images need to
use as their base. An example Dockerfile could be as follows:

```Dockerfile
FROM varrrro/shipyard-server:latest

COPY . .

RUN gcc * -L$LIB_DIR -l$LIB_NAME -I$SRC_DIR -o task

CMD [ "./task" ]
```

Then, in the task's code, the developer just needs to include the library and
call the `set_sched` function before the task's main logic. This functions obtains the scheduling parameters
from environment variables and uses them to set the `SCHED_DEADLINE` policy.
These environment variables are given to the container by the server when the
task is deployed on a node.
