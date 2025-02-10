**⚡ Concurrent Resource Management System**
===========================================

**📌 Overview**
---------------

This project implements a **concurrent resource management system** using **POSIX threads (pthreads), mutexes, condition variables, and semaphores**. It models a scenario where multiple **clients** access a **shared resource with limited capacity**, while **maintenance operations** require **exclusive access**.

The system ensures that:\
✅ Multiple **clients** can access the resource **simultaneously**, up to a defined capacity.\
✅ **Maintenance operations** **block client access** until they complete.\
✅ Clients must **wait** if the resource is **full** or **maintenance is in progress**.\
✅ **Synchronization mechanisms** prevent **race conditions** and ensure safe **concurrent access**.

* * * * *

**✨ Features**
--------------

🔹 **Resource Capacity Control**: Ensures only a limited number of clients can use the resource at a time.\
🔹 **Exclusive Maintenance Access**: Blocks new clients while maintenance is ongoing.\
🔹 **Thread Synchronization**: Uses mutexes, semaphores, and condition variables to prevent race conditions.\
🔹 **Non-Blocking Behavior**: Clients attempting to enter a full resource **must wait**.

* * * * *

**🔧 Implementation Details**
-----------------------------

### **1️⃣ Core Components**

### **📂 `resource_manager.c` (Resource Management Logic)**

-   **Initializes** the system (`resource_manager_init`) with a **specified capacity**.
-   **Client Management (`resource_client_enter`, `resource_client_leave`)**:
    -   Clients **enter** if there is space and **no ongoing maintenance**.
    -   If full, clients must **wait** for an available slot.
-   **Maintenance (`resource_maintenance_enter`, `resource_maintenance_leave`)**:
    -   **Can only start** once all clients have **left**.
    -   **Prevents new clients** from entering until completed.
-   Uses **mutexes** and **condition variables** for **thread synchronization**.

### **📂 `resource_utils.c` (Helper Functions)**

-   Defines **client** and **maintenance** structures.
-   Implements **entry and exit behavior** for **clients** and **maintenance**.
-   Includes `msleep()` for **controlled execution timing**.

### **📂 `example_clients.c` (Basic Usage Example)**

-   Simulates **clients entering and leaving** the resource.
-   Ensures **capacity limits** are enforced correctly.

### **📂 `example_maintenance.c` (Client & Maintenance Interaction Example)**

-   Demonstrates how **maintenance operations block new clients**.
-   Shows **clients waiting** when **maintenance is in progress**.

* * * * *

**💻 How to Use**
-----------------

### **🔧 Building the Project**

Ensure you have **GCC and Make** installed, then compile using:

`make`

### **▶️ Running a Simulation**

To test how clients and maintenance interact:

`./example_clients`

or

`./example_maintenance`

### **📥 Input**

-   **Maximum Resource Capacity** (set in `resource_manager_init`).
-   **Client and Maintenance Requests** (handled via `resource_client_enter`, `resource_maintenance_enter`, etc.).

### **📤 Output**

-   **Logs of clients entering/leaving**.
-   **Messages when maintenance starts and ends**.
-   **Synchronization demonstration** ensuring **safe concurrent access**.

* * * * *

**📊 Example Execution Logs**
-----------------------------

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

✅ **Priority scheduling** for urgent maintenance requests.\
✅ **Timeouts** for clients waiting to enter.\
✅ **Multi-resource environments** for complex scenarios.

* * * * *

**📜 License**
--------------

This project is open-source under the **MIT License**.
