# Small Clinic Management System

**Object-Oriented Programming Assignment using C++**

---

## 📋 Project Overview

This project implements a Small Clinic Management System designed to handle the core operations of a family clinic. The system demonstrates key Object-Oriented Programming (OOP) concepts including **classes**, **objects**, **inheritance**, **polymorphism**, and **encapsulation**.

### 🎯 Key Features
- Patient registration and management (regular and chronic patients)
- Doctor registration with specialization tracking
- Appointment scheduling, completion, and cancellation
- Medical history tracking and updates
- Inheritance-based patient classification with method overriding
- Comprehensive error handling and input validation

### 🏗️ System Architecture
The system consists of 5 main classes that work together to provide a complete clinic management solution:
- **Patient** (Base class)
- **ChronicPatient** (Derived class - demonstrates inheritance)
- **Doctor** (Medical staff management)
- **Appointment** (Scheduling and status tracking)
- **ClinicManagementSystem** (Main system controller)

---

## 🔍 Object-Oriented Analysis (OOA)

### Step 1: Objects Identification
From the clinic scenario, key objects were identified:
- **Patient**: Individuals seeking medical care
- **ChronicPatient**: Patients with ongoing medical conditions
- **Doctor**: Medical professionals providing care
- **Appointment**: Scheduled medical visits
- **ClinicManagementSystem**: Main system coordinator

### Step 2: Attributes Analysis
Each object contains specific data attributes:

**Patient Class:**
- `name` (string) - Patient's full name
- `patientID` (int) - Unique identifier
- `age` (int) - Patient's age
- `medicalHistory` (vector<string>) - Medical records

**ChronicPatient Class (inherits from Patient):**
- `conditionType` (string) - Type of chronic condition
- `lastCheckupDate` (string) - Date of last checkup

**Doctor Class:**
- `name`, `doctorID`, `specialty` - Basic information
- `appointmentIDs` (vector<int>) - Assigned appointments

**Appointment Class:**
- `appointmentID`, `date`, `time`, `reason` - Basic info
- `status` (enum) - SCHEDULED/COMPLETED/CANCELED
- `patientID`, `doctorID` - Relationships

### Step 3: Methods Analysis
Key behaviors identified for each class:

**Patient Methods:**
- Getters/Setters for all attributes
- `addMedicalRecord()` - Add treatment records
- `getAppointmentFrequency()` - Virtual method (overridable)
- `getPatientType()` - Virtual method for classification
- `displayInfo()` - Virtual method for information display

**ChronicPatient Override Methods:**
- `getAppointmentFrequency()` → "Every 3 months" (vs "As needed")
- `getPatientType()` → "Chronic Patient" (vs "Regular Patient")
- `displayInfo()` → Includes chronic condition details

### Step 4: Inheritance Relationships
**Primary Inheritance:**
```
Patient (Base Class)
    ↓
ChronicPatient (Derived Class)
```

**Inheritance Benefits:**
- **Code Reuse**: ChronicPatient inherits all Patient functionality
- **Polymorphism**: Patient pointers can reference both types
- **Method Override**: Specialized behavior for chronic patients
- **Extensibility**: Easy to add new patient types

---

## 💻 Implementation Details

### Class Design Architecture

#### 1. Inheritance Implementation
```cpp
class Patient {
protected:  // Allows access by derived classes
    string name;
    int patientID;
    int age;
    vector<string> medicalHistory;
    
public:
    virtual ~Patient() {}  // Virtual destructor
    virtual string getAppointmentFrequency() const;  // Overridable
    virtual string getPatientType() const;           // Overridable
    virtual void displayInfo() const;                // Overridable
};

class ChronicPatient : public Patient {  // Public inheritance
private:
    string conditionType;
    string lastCheckupDate;
    
public:
    // Override virtual methods
    string getAppointmentFrequency() const override;
    string getPatientType() const override;
    void displayInfo() const override;
};
```

#### 2. Key OOP Concepts Demonstrated

**Encapsulation:**
- Private attributes with public method interfaces
- Data hiding and controlled access

**Inheritance:**
- Single inheritance: ChronicPatient extends Patient
- Method overriding for specialized behavior

**Polymorphism:**
- Virtual methods enable runtime method resolution
- Patient pointers can reference both base and derived objects

**Abstraction:**
- Clean interfaces hide implementation complexity
- High-level operations through method calls

### 3. Advanced Features
- **STL Containers**: Dynamic collections using vector<>
- **Static Members**: Automatic appointment ID generation
- **Enumerations**: Type-safe status tracking
- **Memory Management**: Proper destructor cleanup
- **Error Handling**: Input validation and graceful error messages

---

## 🧪 Testing and Results

### Test Categories

#### 1. Basic Functionality Testing
```
✅ Test 1: Adding Patients
- Regular patient added successfully. ID: 1
- Chronic patient added successfully. ID: 2
- Regular patient added successfully. ID: 3

✅ Test 2: Adding Doctors
- Doctor added successfully. ID: 1
- Doctor added successfully. ID: 2

✅ Test 3: Scheduling Appointments
- Appointment scheduled successfully. Appointment ID: 1
- Appointment scheduled successfully. Appointment ID: 2
- Appointment scheduled successfully. Appointment ID: 3

✅ Test 4: Completing Appointments
- Appointment 1 completed successfully.
- Medical record added to patient history

✅ Test 5: Canceling Appointments
- Appointment 3 canceled successfully.
```

#### 2. Inheritance and Polymorphism Testing
```
🔄 Polymorphism Demonstration:
- Regular Patient Frequency: "As needed"
- Chronic Patient Frequency: "Every 3 months (chronic condition)"

📋 Method Override Demonstration:
- Patient 1 Type: "Regular Patient"
- Patient 2 Type: "Chronic Patient"
```

#### 3. Error Handling Testing
```
❌ Error Cases Successfully Handled:
- Invalid Patient ID: "Error: Invalid patient ID."
- Invalid Doctor ID: "Error: Invalid doctor ID."
- Invalid Appointment ID: "Error: Appointment ID not found."
- Double Cancellation: "Appointment 3 is already canceled."
```

### Test Results Analysis
- ✅ All core functionalities work correctly
- ✅ Inheritance and polymorphism properly implemented
- ✅ Error handling provides meaningful feedback
- ✅ Memory management prevents leaks
- ✅ Data relationships maintained consistently

---

## 🤖 AI Usage Documentation

### How AI Assisted This Project

I used **Claude AI** to assist in multiple aspects of this project while ensuring I understood and wrote all the code myself:

#### 1. **Brainstorming and Planning**
**Prompt Used:** *"Help me brainstorm methods and attributes for a Patient class in a clinic management system. What would be essential features?"*

**AI Contribution:** Suggested core attributes like name, ID, age, medical history, and methods like addMedicalRecord(), displayInfo(). I adapted these suggestions to fit my specific design requirements.

#### 2. **Inheritance Design Consultation**
**Prompt Used:** *"How should I implement inheritance for different types of patients in a clinic system? What methods should be virtual?"*

**AI Contribution:** Recommended making appointment frequency and patient type as virtual methods, which I implemented as `getAppointmentFrequency()` and `getPatientType()`.

#### 3. **Test Case Generation**
**Prompt Used:** *"What test cases should I create to demonstrate OOP concepts in a clinic management system?"*

**AI Contribution:** Suggested testing basic functionality, inheritance behavior, error handling, and polymorphism. I expanded these into comprehensive test functions with specific scenarios.

#### 4. **Error Handling Strategies**
**Prompt Used:** *"What error conditions should I handle in a clinic appointment scheduling system?"*

**AI Contribution:** Identified invalid IDs, duplicate operations, and status conflicts. I implemented validation logic and meaningful error messages based on these suggestions.

#### 5. **Code Structure Optimization**
**Prompt Used:** *"How should I organize my C++ classes for better maintainability?"*

**AI Contribution:** Suggested forward declarations, proper header organization, and separation of concerns. I applied these principles in my final implementation.

### Ethical AI Usage
- Used AI as a **brainstorming partner**, not a code generator
- Always **understood and validated** AI suggestions before implementation
- **Customized all suggestions** to fit my specific project requirements
- **Maintained academic integrity** by writing original code

---

## 🚀 How to Compile and Run

### Requirements
- C++ compiler (g++, clang++, or Visual Studio)
- C++11 or later standard

### Compilation
```bash
g++ -std=c++11 -o clinic_system main.cpp
```

### Execution
```bash
./clinic_system
```

### Expected Output
The program will run comprehensive tests demonstrating all OOP features with detailed console output showing system operations and results.

---


---

*This project demonstrates practical application of Object-Oriented Programming principles in a real-world healthcare management scenario, showcasing the power of inheritance, polymorphism, and proper software design.*
