# Object-Oriented Programming Week 4 Assignment
## Small Clinic Management System

**Student Name:** Doan Trong Trung  
**Student ID:** 24110140  
**Assignment:** Week 4 - Inheritance and Class Design  

---

## Step 1: Object-Oriented Analysis (OOA) Model

### 1.1 Identify Objects (Nouns)
From the Small Clinic Management System scenario, the key objects identified are:
- **Patient** - individuals seeking medical care
- **ChronicPatient** - patients with long-term medical conditions
- **Doctor** - medical practitioners providing care
- **Appointment** - scheduled meetings between patients and doctors
- **Medicine** - pharmaceutical products used for treatment
- **Prescription** - medical orders for specific treatments
- **Bill** - financial records for services and medications
- **ClinicManagementSystem** - overall system controller

### 1.2 Identify Attributes (Descriptive Nouns)
**Patient:**
- name, patientID, age, medicalHistory

**ChronicPatient:**
- conditionType, lastCheckupDate (inherits Patient attributes)

**Doctor:**
- name, doctorID, specialty, appointmentIDs

**Appointment:**
- appointmentID, date, time, reason, status, patientID, doctorID

**Medicine:**
- medicineID, name, description, price, stockQuantity, expiryDate, manufacturer

**Prescription:**
- prescriptionID, patientID, doctorID, medicines, prescriptionDate, instructions

**Bill:**
- billID, patientID, consultationFee, medicationCost, totalAmount, billDate, isPaid

### 1.3 Identify Methods (Verbs)
**Patient:**
- addMedicalRecord(), displayInfo(), getAppointmentFrequency(), getPatientType()

**ChronicPatient:**
- displayInfo() [overridden], getAppointmentFrequency() [overridden], setLastCheckupDate()

**Doctor:**
- assignAppointment(), removeAppointment(), displayInfo()

**Appointment:**
- reschedule(), setStatus(), displayInfo(), getStatusString()

**Medicine:**
- isExpired(), checkStock(), updateStock(), prescribe()

**Prescription:**
- addMedicine(), calculateTotalCost(), printPrescription()

**Bill:**
- processPayment(), printBill()

**ClinicManagementSystem:**
- addPatient(), addDoctor(), scheduleAppointment(), cancelAppointment(), displayAllPatients()

### 1.4 Identify Inheritance Relationships
**Primary Inheritance:**
- `ChronicPatient` inherits from `Patient` (IS-A relationship)
  - ChronicPatient IS-A Patient with additional chronic condition management
  - Overrides virtual methods for specialized behavior

**Rationale for Inheritance Design:**
- Used inheritance only where meaningful specialization exists
- ChronicPatient extends Patient with chronic-specific attributes and behaviors
- Other classes use composition/association rather than forced inheritance

---

## Step 2: Class Design and Implementation

### Inheritance Implementation
```cpp
class Patient {
protected:
    string name;
    int patientID;
    int age;
    vector<string> medicalHistory;

public:
    Patient(const string& name, int id, int age) 
        : name(name), patientID(id), age(age) {}
    
    virtual ~Patient() {} // Virtual destructor for proper inheritance
    
    virtual string getAppointmentFrequency() const {
        return "As needed";
    }
    
    virtual string getPatientType() const {
        return "Regular Patient";
    }
    
    virtual void displayInfo() const { /* implementation */ }
};

class ChronicPatient : public Patient {
private:
    string conditionType;
    string lastCheckupDate;

public:
    ChronicPatient(const string& name, int id, int age, 
                   const string& condition, const string& lastCheckup)
        : Patient(name, id, age), conditionType(condition), 
          lastCheckupDate(lastCheckup) {}
    
    // Override virtual methods for specialized behavior
    string getAppointmentFrequency() const override {
        return "Every 3 months (chronic condition)";
    }
    
    string getPatientType() const override {
        return "Chronic Patient";
    }
    
    void displayInfo() const override {
        Patient::displayInfo(); // Call base class method
        cout << "Chronic Condition: " << conditionType << endl;
        cout << "Last Checkup: " << lastCheckupDate << endl;
    }
};
```

### Key Design Features
- **Virtual Functions**: Enable polymorphic behavior for different patient types
- **Constructor Chaining**: Derived class properly initializes base class using initialization list
- **Method Overriding**: ChronicPatient overrides virtual methods for specialized behavior
- **Encapsulation**: Private/protected access modifiers control data access
- **Memory Management**: Virtual destructor ensures proper cleanup in inheritance hierarchy

### System Architecture
The system implements 7 classes total:
1. **Patient** (base class)
2. **ChronicPatient** (derived class) 
3. **Doctor** - manages medical practitioners
4. **Appointment** - handles scheduling with enum status system
5. **Medicine** - inventory management with stock control
6. **Prescription** - links patients, doctors, and medicines
7. **Bill** - financial management with automatic cost calculation

---

## Step 3: Testing and Results

### Test Case 1: Inheritance and Polymorphism
**Objective**: Demonstrate virtual function behavior through base class pointers

```cpp
// Creating different patient types
cms.addPatient("Doan Trong Trung", 22);
cms.addChronicPatient("Pham Van Hoa", 60, "Diabetes", "2025-08-10");
```

**Output:**
```
=== ALL PATIENTS ===

--- Patient 1 ---
Patient Type: Regular Patient
Name: Doan Trong Trung
ID: 1
Age: 22
Appointment Frequency: As needed

--- Patient 2 ---
Patient Type: Chronic Patient
Name: Pham Van Hoa
ID: 2
Age: 60
Appointment Frequency: Every 3 months (chronic condition)
Chronic Condition: Diabetes
Last Checkup: 2025-08-10
```

**What This Demonstrates**: Polymorphic behavior working correctly - same `displayInfo()` call produces different outputs based on actual object type.

### Test Case 2: Appointment Scheduling with Virtual Method Override
**Objective**: Show how ChronicPatient overrides appointment frequency logic

```cpp
Patient* regularPatient = cms.findPatient(1);
Patient* chronicPatient = cms.findPatient(2);

cout << "Regular patient frequency: " << regularPatient->getAppointmentFrequency() << endl;
cout << "Chronic patient frequency: " << chronicPatient->getAppointmentFrequency() << endl;
```

**Output:**
```
Regular patient frequency: As needed
Chronic patient frequency: Every 3 months (chronic condition)
```

**What This Demonstrates**: Virtual function override working through base class pointers - different behaviors for different patient types.

### Test Case 3: Complete System Integration
**Objective**: Demonstrate full workflow from patient registration to billing

**Operations Performed:**
1. Add patients and doctors
2. Schedule appointments
3. Create prescriptions with medicines
4. Generate bills automatically

**Sample Output:**
```
Appointment scheduled successfully. Appointment ID: 1
Prescription created. ID: 1 for Patient ID: 1
Bill generated successfully. Bill ID: 1

Bill ID: 1 | Patient ID: 1
Consultation Fee: $20 | Medication Cost: $5
Total Amount: $25 | Status: Unpaid
```

**What This Demonstrates**: Proper object relationships and data flow between all system components.

---

## Step 4: LLM Usage Documentation

### How I Used AI Assistance

**1. Initial Class Structure Brainstorming**
*Prompt*: "Help me identify the main classes needed for a small clinic management system with inheritance."
*AI Response*: Suggested Patient as base class with specialized derived classes, plus supporting classes for Doctor, Appointment.
*How I Used It*: Applied the Patient→ChronicPatient inheritance suggestion, added my own Medicine, Prescription, and Bill classes.

**2. Virtual Function Design**
*Prompt*: "What methods should be virtual in a Patient class to demonstrate polymorphism?"
*AI Response*: Recommended virtual methods for patient type identification and appointment frequency.
*How I Used It*: Implemented `getPatientType()`, `getAppointmentFrequency()`, and `displayInfo()` as virtual methods.

**3. Testing Strategy**
*Prompt*: "How should I test inheritance and polymorphism in C++?"
*AI Response*: Suggested creating objects through base class pointers and calling virtual methods.
*How I Used It*: Developed comprehensive test cases showing polymorphic behavior and method overriding.

**Ethical Usage**: Used AI for conceptual guidance only. All code implementation, logic design, and creative decisions were my original work.

---

## Conclusion

This assignment successfully demonstrates mastery of object-oriented programming principles through a practical clinic management system:

### Technical Achievements
- **Proper Inheritance**: Implemented meaningful Patient→ChronicPatient hierarchy
- **Polymorphism**: Virtual functions enable different behaviors through same interface  
- **5+ Classes**: System includes 7 interconnected classes with proper relationships
- **Complete Functionality**: Full workflow from patient registration to billing
- **Error Handling**: Comprehensive input validation and status checking
- **Modern C++**: Uses override specifiers, const correctness, and RAII principles

### OOP Principles Demonstrated
1. **Inheritance**: Meaningful specialization for chronic patients
2. **Polymorphism**: Runtime method binding through virtual functions
3. **Encapsulation**: Proper access control with private/protected members
4. **Abstraction**: Clean interfaces hiding implementation complexity

### System Capabilities
The completed system handles patient management, appointment scheduling, prescription creation, medicine inventory, and automated billing - demonstrating real-world applicability of OOP concepts.

**Compilation**: `g++ -std=c++11 -o clinic 24110140_DoanTrongTrung_Week4_Assignment.cpp`
**Execution**: System includes sample data and interactive menu for immediate testing.
