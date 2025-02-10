**Concurrent Resource Management System**
=========================================

**Overview**
------------

This project implements a **concurrent resource management system** using **POSIX threads (pthreads), mutexes, condition variables, and semaphores**. It models a scenario where multiple users (clients) access a **shared resource with limited capacity**, while maintenance (cleaning) operations must occasionally take place, requiring exclusive access.

The system ensures that:\
✅ Multiple clients can access the resource simultaneously, up to a defined capacity.\
✅ Maintenance operations **block client access** until they complete.\
✅ Clients must **wait if the resource is full** or if maintenance is in progress.\
✅ Synchronization ensures **safe concurrent access** without race conditions.

**Features**
------------

-   **Resource Capacity Control**: Ensures only a limited number of clients can use the resource at a time.
-   **Exclusive Maintenance Access**: Blocks new clients while maintenance is ongoing.
-   **Thread Synchronization**: Uses mutexes, semaphores, and condition variables to prevent race conditions.
-   **Non-Blocking Behavior**: Clients attempting to enter a full resource must wait.

* * * * *

**Implementation Details**
--------------------------

### **1️⃣ Core Components**

### **🔹 `dining.c` (Resource Management Logic)**

-   **Initializes the system (`dining_init`)** with a specified capacity.
-   **Clients (`dining_client_enter`, `dining_client_leave`)**:
    -   Clients can enter if there is space and no maintenance is in progress.
    -   If full, they wait for an available slot.
-   **Maintenance (`dining_maintenance_enter`, `dining_maintenance_leave`)**:
    -   Can only begin when all clients leave.
    -   Blocks new clients from entering until completed.
-   Uses **mutexes** and **condition variables** for synchronization.

### **🔹 `utils.c` (Helper Functions)**

-   Defines **client** and **maintenance** structures.
-   Implements **entry and exit behavior** for clients and maintenance.
-   Contains a `msleep()` function for controlled execution timing.

### **🔹 `example1.c` (Basic Usage)**

-   Simulates **clients entering and leaving** the resource.
-   Ensures **capacity limits are enforced**.

### **🔹 `example2.c` (Client & Maintenance Interactions)**

-   Demonstrates how maintenance blocks new clients.
-   Shows clients waiting when **maintenance is in progress**.

* * * * *

**💻 Usage**
------------

### **🔧 Building the Project**

Ensure you have **GCC and Make** installed, then compile using:

`make`

### **▶️ Running a Simulation**

To test how clients and maintenance interact:

`./example1`

or

`./example2`

### **📥 Input**

-   **Maximum Resource Capacity** (defined in `dining_init`).
-   **Client and Maintenance Requests** (handled by functions like `dining_client_enter`).

### **📤 Output**

-   Logs of **clients entering/leaving**.
-   Messages when **maintenance begins and ends**.
-   Demonstrates **synchronization and concurrency control**.

* * * * *

**Example Execution Logs**
--------------------------

### **Example 1: Clients Entering & Leaving**

`Client 1 comes in`  
`Client 1 entered`   
`Client 2 comes in`  
`Client 2 entered`  
`Client 3 comes in`  
`Client 3 entered`  
`Client 4 comes in (waiting - resource is full)`  
`Client 1 leaves`  
`Client 4 entered`  
`Client 2 leaves`  
`Client 3 leaves`  
`Client 4 leaves `

### **Example 2: Maintenance Blocks Clients**

`Client 1 comes in`  
`Client 1 entered`  
`Maintenance 1 tries to enter (waiting for clients to leave)`  
`Client 1 leaves`  
`Maintenance 1 started`  
`Client 2 tries to enter (waiting - maintenance in progress)`  
`Maintenance 1 completed`  
`Client 2 entered`  
`Client 2 leaves `

* * * * *

**🔮 Future Enhancements**
--------------------------

✅ Add **priority scheduling** for urgent maintenance requests.\
✅ Implement **timeouts** for waiting clients.\
✅ Extend to **multi-resource environments**.

* * * * *

**📜 License**
--------------

This project is open-source under the **MIT License**.
