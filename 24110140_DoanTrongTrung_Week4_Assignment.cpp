#include <bits/stdc++.h>
using namespace std;

// Forward declarations
class Doctor;
class Appointment;

// Base Patient class
class Patient {
protected:
    string name;
    int patientID;
    int age;
    vector<string> medicalHistory;

public:
    // Constructor
    Patient(const string& name, int id, int age) 
        : name(name), patientID(id), age(age) {}
    
    // Virtual destructor for proper inheritance
    virtual ~Patient() {}
    
    // Getters
    string getName() const { return name; }
    int getPatientID() const { return patientID; }
    int getAge() const { return age; }
    vector<string> getMedicalHistory() const { return medicalHistory; }
    
    // Methods
    void addMedicalRecord(const string& record) {
        medicalHistory.push_back(record);
    }
    
    // Virtual method for scheduling appointments (to be overridden)
    virtual string getAppointmentFrequency() const {
        return "As needed";
    }
    
    // Virtual method for patient type
    virtual string getPatientType() const {
        return "Regular Patient";
    }
    
    // Display patient information
    virtual void displayInfo() const {
        cout << "Patient Type: " << getPatientType() << endl;
        cout << "Name: " << name << endl;
        cout << "ID: " << patientID << endl;
        cout << "Age: " << age << endl;
        cout << "Appointment Frequency: " << getAppointmentFrequency() << endl;
        cout << "Medical History: ";
        if (medicalHistory.empty()) {
            cout << "None recorded" << endl;
        } else {
            cout << endl;
            for (const auto& record : medicalHistory) {
                cout << "  - " << record << endl;
            }
        }
    }
};

// Derived ChronicPatient class (demonstrating inheritance)
class ChronicPatient : public Patient {
private:
    string conditionType;
    string lastCheckupDate;

public:
    // Constructor
    ChronicPatient(const string& name, int id, int age, 
                   const string& condition, const string& lastCheckup)
        : Patient(name, id, age), conditionType(condition), lastCheckupDate(lastCheckup) {}
    
    // Getters
    string getConditionType() const { return conditionType; }
    string getLastCheckupDate() const { return lastCheckupDate; }
    
    // Setters
    void setLastCheckupDate(const string& date) { lastCheckupDate = date; }
    
    // Override virtual methods
    string getAppointmentFrequency() const override {
        return "Every 3 months (chronic condition)";
    }
    
    string getPatientType() const override {
        return "Chronic Patient";
    }
    
    // Override display method
    void displayInfo() const override {
        Patient::displayInfo(); // Call base class method
        cout << "Chronic Condition: " << conditionType << endl;
        cout << "Last Checkup: " << lastCheckupDate << endl;
    }
};

// Doctor class
class Doctor {
private:
    string name;
    int doctorID;
    string specialty;
    vector<int> appointmentIDs; // Store appointment IDs assigned to this doctor

public:
    // Constructor
    Doctor(const string& name, int id, const string& specialty)
        : name(name), doctorID(id), specialty(specialty) {}
    
    // Getters
    string getName() const { return name; }
    int getDoctorID() const { return doctorID; }
    string getSpecialty() const { return specialty; }
    vector<int> getAppointmentIDs() const { return appointmentIDs; }
    
    // Methods
    void assignAppointment(int appointmentID) {
        appointmentIDs.push_back(appointmentID);
    }
    
    void removeAppointment(int appointmentID) {
        appointmentIDs.erase(
            remove(appointmentIDs.begin(), appointmentIDs.end(), appointmentID),
            appointmentIDs.end()
        );
    }
    
    void displayInfo() const {
        cout << "Doctor: " << name << endl;
        cout << "ID: " << doctorID << endl;
        cout << "Specialty: " << specialty << endl;
        cout << "Assigned Appointments: " << appointmentIDs.size() << endl;
    }
};

// Appointment class
class Appointment {
public:
    enum Status { SCHEDULED, COMPLETED, CANCELED };
    
private:
    static int nextAppointmentID;
    int appointmentID;
    string date;
    string time;
    string reason;
    Status status;
    int patientID;
    int doctorID;

public:
    // Constructor
    Appointment(const string& date, const string& time, 
                const string& reason, int patientID, int doctorID)
        : appointmentID(nextAppointmentID++), date(date), time(time), 
          reason(reason), status(SCHEDULED), patientID(patientID), doctorID(doctorID) {}
    
    // Getters
    int getAppointmentID() const { return appointmentID; }
    string getDate() const { return date; }
    string getTime() const { return time; }
    string getReason() const { return reason; }
    Status getStatus() const { return status; }
    int getPatientID() const { return patientID; }
    int getDoctorID() const { return doctorID; }
    
    // Methods
    void setStatus(Status newStatus) { status = newStatus; }
    
    string getStatusString() const {
        switch (status) {
            case SCHEDULED: return "Scheduled";
            case COMPLETED: return "Completed";
            case CANCELED: return "Canceled";
            default: return "Unknown";
        }
    }
    
    void displayInfo() const {
        cout << "Appointment ID: " << appointmentID << endl;
        cout << "Date: " << date << endl;
        cout << "Time: " << time << endl;
        cout << "Reason: " << reason << endl;
        cout << "Status: " << getStatusString() << endl;
        cout << "Patient ID: " << patientID << endl;
        cout << "Doctor ID: " << doctorID << endl;
    }

    void reschedule(const string& newDate , const string& newTime) {
        if (status == SCHEDULED) {
            date = newDate;
            time = newTime;
            cout << "Appointment rescheduled to: " << newDate << " at " << newTime << endl;
        } else {
            cout << "Cannot reschedule. Current status: " << getStatusString() << endl;

        }
    }
};

// Medicine class
class Medicine {
private:
    int medicineID;
    string name;
    string description;
    double price;
    int stockQuantity;
    string expiryDate;
    string manufacturer;

public:
    Medicine(int id, string n, string desc, double p, int stock, string exp, string manu)
        : medicineID(id), name(n), description(desc), price(p),
          stockQuantity(stock), expiryDate(exp), manufacturer(manu) {}

    bool isExpired(string currentDate) {
        return expiryDate < currentDate;
    }

    bool checkStock(int quantity) {
        return stockQuantity >= quantity;
    }

    void updateStock(int quantity) {
        if (quantity <= stockQuantity) stockQuantity -= quantity;
    }

    void prescribe() {
        cout << "Prescribed: " << name << " - " << description << endl;
    }

    double getPrice() const { return price; }
    string getName() const { return name; }
};

// Prescription class
class Prescription {
private:
    int prescriptionID;
    int patientID;
    int doctorID;
    vector<Medicine> medicines;
    string prescriptionDate;
    string instructions;

public:
    Prescription(int prid, int pid, int did, string date, string instr)
        : prescriptionID(prid), patientID(pid), doctorID(did), prescriptionDate(date), instructions(instr) {}

    void addMedicine(const Medicine& med) {
        medicines.push_back(med);
    }

    double calculateTotalCost() const {
        double total = 0;
        for (const auto& med : medicines) {
            total += med.getPrice();
        }
        return total;
    }

    void printPrescription() const {
        cout << "Prescription ID: " << prescriptionID << endl;
        cout << "Patient ID: " << patientID << endl;
        cout << "Doctor ID: " << doctorID << endl;
        cout << "Date: " << prescriptionDate << endl;
        cout << "Instructions: " << instructions << endl;
        cout << "Medicines:" << endl;
        for (const auto& med : medicines) {
            cout << "- " << med.getName() << " ($" << med.getPrice() << ")" << endl;
        }
    }

    int getPrescriptionID() const {
    return prescriptionID;
    }   

    int getPatientID() const {
        return patientID;
    }

};

// Bill/Invoice Class
class Bill {
private:
    int billID;
    int patientID;
    double consultationFee;
    double medicationCost;
    double totalAmount;
    string billDate;
    bool isPaid;

public:
    Bill(int bid, int pid, double fee, double medCost, const string& date)
        : billID(bid), patientID(pid),
          consultationFee(fee), medicationCost(medCost),
          billDate(date), isPaid(false) {
        totalAmount = consultationFee + medicationCost;
    }

    void processPayment() {
        isPaid = true;
        cout << "Payment processed for Bill ID: " << billID << endl;
    }

    void printBill() const {
        cout << "Bill ID: " << billID << "\nPatient ID: " << patientID
             << "\nConsultation Fee: $" << consultationFee
             << "\nMedication Cost: $" << medicationCost
             << "\nTotal Amount: $" << totalAmount
             << "\nBill Date: " << billDate
             << "\nStatus: " << (isPaid ? "Paid" : "Unpaid") << endl;
    }
};

// Initialize static member
int Appointment::nextAppointmentID = 1;

// Clinic Management System class
class ClinicManagementSystem {
private:
    vector<Patient*> patients;
    vector<Doctor> doctors;
    vector<Appointment> appointments;
    vector<Medicine> medicineInventory;
    vector<Prescription> prescriptions;
    vector<Bill> bills;

public:
    // Destructor to clean up dynamic memory
    ~ClinicManagementSystem() {
        for (Patient* patient : patients) {
            delete patient;
        }
    }
    
    // Add regular patient
    void addPatient(const string& name, int age) {
        int id = patients.size() + 1;
        patients.push_back(new Patient(name, id, age));
        cout << "Regular patient added successfully. ID: " << id << endl;
    }
    
    // Add chronic patient
    void addChronicPatient(const string& name, int age, 
                          const string& condition, const string& lastCheckup) {
        int id = patients.size() + 1;
        patients.push_back(new ChronicPatient(name, id, age, condition, lastCheckup));
        cout << "Chronic patient added successfully. ID: " << id << endl;
    }
    
    // Add doctor
    void addDoctor(const string& name, const string& specialty) {
        int id = doctors.size() + 1;
        doctors.push_back(Doctor(name, id, specialty));
        cout << "Doctor added successfully. ID: " << id << endl;
    }

    // Add medicine to inventory
    void addMedicine(const Medicine& med) {
        medicineInventory.push_back(med);
        cout << "Medicine added: " << med.getName() << endl;
    }

    // Getter for medicine inventory
    const vector<Medicine>& getMedicineInventory() const {
        return medicineInventory;
    }
    
    // Create prescription
    void createPrescription(int patientID, int doctorID, const string& date, const string& instructions, const vector<int>& medicineIDs) {
        if (patientID < 1 || patientID > static_cast<int>(patients.size())) {
            cout << "Error: Invalid patient ID." << endl;
            return;
        }
        if (doctorID < 1 || doctorID > static_cast<int>(doctors.size())) {
            cout << "Error: Invalid doctor ID." << endl;
            return;
        }

        int prescriptionID = prescriptions.size() + 1;

        Prescription p(prescriptionID, patientID, doctorID, date, instructions);

        for (int id : medicineIDs) {
            if (id >= 1 && id <= static_cast<int>(medicineInventory.size())) {
                p.addMedicine(medicineInventory[id - 1]);
            } else {
                cout << "Invalid medicine ID: " << id << endl;
            }
        }

        prescriptions.push_back(p);
        cout << "Prescription created. ID: " << prescriptionID << " for Patient ID: " << patientID << endl;
    }

    // Generate bill
    void generateBill(int prescriptionID, double consultationFee, const string& billDate) {
        for (const auto& p : prescriptions) {
            if (p.getPrescriptionID() == prescriptionID) {
                int patientID = p.getPatientID();
                double medicationCost = p.calculateTotalCost();
                int billID = bills.size() + 1;

                Bill b(billID, patientID, consultationFee, medicationCost, billDate);
                bills.push_back(b);

                cout << "Bill generated successfully. Bill ID: " << billID << endl;
                return;
            }
        }
        cout << "Error: Prescription ID not found." << endl;
    }

    // Schedule appointment
    bool scheduleAppointment(const string& date, const string& time,
                           const string& reason, int patientID, int doctorID) {
        // Validate patient and doctor IDs
        if (patientID < 1 || patientID > static_cast<int>(patients.size())) {
            cout << "Error: Invalid patient ID." << endl;
            return false;
        }
        if (doctorID < 1 || doctorID > static_cast<int>(doctors.size())) {
            cout << "Error: Invalid doctor ID." << endl;
            return false;
        }
        
        appointments.push_back(Appointment(date, time, reason, patientID, doctorID));
        int appointmentID = appointments.back().getAppointmentID();
        
        // Assign appointment to doctor
        doctors[doctorID - 1].assignAppointment(appointmentID);
        
        cout << "Appointment scheduled successfully. Appointment ID: " << appointmentID << endl;
        return true;
    }
    
    // Cancel appointment
    bool cancelAppointment(int appointmentID) {
        for (auto& appointment : appointments) {
            if (appointment.getAppointmentID() == appointmentID) {
                if (appointment.getStatus() != Appointment::CANCELED) {
                    appointment.setStatus(Appointment::CANCELED);
                    
                    // Remove from doctor's appointment list
                    int doctorID = appointment.getDoctorID();
                    doctors[doctorID - 1].removeAppointment(appointmentID);
                    
                    cout << "Appointment " << appointmentID << " canceled successfully." << endl;
                    return true;
                } else {
                    cout << "Appointment " << appointmentID << " is already canceled." << endl;
                    return false;
                }
            }
        }
        cout << "Error: Appointment ID not found." << endl;
        return false;
    }
    
    // Complete appointment
    bool completeAppointment(int appointmentID, const string& treatmentRecord) {
        for (auto& appointment : appointments) {
            if (appointment.getAppointmentID() == appointmentID) {
                if (appointment.getStatus() == Appointment::SCHEDULED) {
                    appointment.setStatus(Appointment::COMPLETED);
                    
                    // Add treatment record to patient's medical history
                    int patientID = appointment.getPatientID();
                    patients[patientID - 1]->addMedicalRecord(treatmentRecord);
                    
                    cout << "Appointment " << appointmentID << " completed successfully." << endl;
                    return true;
                } else {
                    cout << "Appointment " << appointmentID << " cannot be completed (not scheduled)." << endl;
                    return false;
                }
            }
        }
        cout << "Error: Appointment ID not found." << endl;
        return false;
    }

    // Reschedule appointment
    bool rescheduleAppointment(int appointmentID, const string& newDate, const string& newTime) {
        for (auto& appointment : appointments) {
            if (appointment.getAppointmentID() == appointmentID) {
                if (appointment.getStatus() == Appointment::SCHEDULED) {
                    appointment.reschedule(newDate, newTime);
                    cout << "Appointment " << appointmentID << " rescheduled successfully." << endl;
                    return true;
                } else {
                    cout << "Cannot reschedule. Appointment is " << appointment.getStatusString() << "." << endl;
                    return false;
                }
            }
        }
        cout << "Error: Appointment ID not found." << endl;
        return false;
    }

    // Display all patients
    void displayAllPatients() const {
        cout << "\n=== ALL PATIENTS ===" << endl;
        if (patients.empty()) {
            cout << "No patients registered." << endl;
            return;
        }
        
        for (size_t i = 0; i < patients.size(); ++i) {
            cout << "\n--- Patient " << (i + 1) << " ---" << endl;
            patients[i]->displayInfo();
        }
    }
    
    // Display all doctors
    void displayAllDoctors() const {
        cout << "\n=== ALL DOCTORS ===" << endl;
        if (doctors.empty()) {
            cout << "No doctors registered." << endl;
            return;
        }
        
        for (size_t i = 0; i < doctors.size(); ++i) {
            cout << "\n--- Doctor " << (i + 1) << " ---" << endl;
            doctors[i].displayInfo();
        }
    }
    
    // Display all appointments
    void displayAllAppointments() const {
        cout << "\n=== ALL APPOINTMENTS ===" << endl;
        if (appointments.empty()) {
            cout << "No appointments scheduled." << endl;
            return;
        }
        
        for (size_t i = 0; i < appointments.size(); ++i) {
            cout << "\n--- Appointment " << (i + 1) << " ---" << endl;
            appointments[i].displayInfo();
        }
    }

    // Display all medicines
    void displayAllMedicines() const {
        cout << "\n=== MEDICINE INVENTORY ===" << endl;
        if (medicineInventory.empty()) {
            cout << "No medicines available." << endl;
            return;
        }
        for (const auto& med : medicineInventory) {
            cout << "- " << med.getName() << " | Price: $" << med.getPrice() << endl;
        }
    }

    // Display all prescriptions
    void displayAllPrescriptions() const {
        cout << "\n=== ALL PRESCRIPTIONS ===" << endl;

        if (prescriptions.empty()) {
            cout << "No prescriptions available." << endl;
            return;
        }

        for (size_t i = 0; i < prescriptions.size(); ++i) {
            cout << "\n--- Prescription " << (i + 1) << " ---" << endl;
            prescriptions[i].printPrescription();
        }
    }

    // Display all bills
    void displayAllBills() const {
        cout << "\n=== BILLS ===" << endl;
        if (bills.empty()) {
            cout << "No bills available." << endl;
            return;
        }
        for (const auto& b : bills) {
            b.printBill();
            cout << "------------------------" << endl;
        }
    }
    
    // Find patient by ID
    Patient* findPatient(int patientID) {
        if (patientID >= 1 && patientID <= static_cast<int>(patients.size())) {
            return patients[patientID - 1];
        }
        return nullptr;
    }
    
    // Find doctor by ID
    Doctor* findDoctor(int doctorID) {
        if (doctorID >= 1 && doctorID <= doctors.size()) {
            return &doctors[doctorID - 1];
        }
        return nullptr;
    }
};

// Function to initialize sample data
void initializeSampleData(ClinicManagementSystem& cms) {
    // Add doctors
    cms.addDoctor("Dr. Nguyen Van Binh", "Cardiology");
    cms.addDoctor("Dr. Tran Thi Mai", "Dermatology");
    cms.addDoctor("Dr. Le Quang Huy", "Pediatrics");

    // Add patients
    cms.addPatient("Doan Trong Trung", 22);
    cms.addPatient("Nguyen Thi Lan", 35);

    // Add chronic patients
    cms.addChronicPatient("Pham Van Hoa", 60, "Diabetes", "2025-08-10");
    cms.addChronicPatient("Le Thi Huong", 55, "Hypertension", "2025-07-20");

    // Add medicines
    cms.addMedicine(Medicine(0, "Paracetamol", "Pain relief", 2.5, 100, "2026-01-01", "PharmaCo"));
    cms.addMedicine(Medicine(1, "Amoxicillin", "Antibiotic", 5.0, 50, "2025-12-31", "HealthMed"));
    cms.addMedicine(Medicine(2, "Metformin", "Diabetes control", 3.2, 80, "2026-03-15", "Glucare"));
    cms.addMedicine(Medicine(3, "Losartan", "Blood pressure", 4.5, 60, "2026-02-10", "CardioPharm"));

    // Create appointments
    cms.scheduleAppointment("2025-09-15", "09:00", "General Checkup", 1, 1);
    cms.scheduleAppointment("2025-09-16", "10:30", "Skin Rash", 2, 2);
    cms.scheduleAppointment("2025-09-17", "08:00", "Diabetes Follow-up", 3, 1);
    cms.scheduleAppointment("2025-09-18", "11:00", "Blood Pressure Review", 4, 3);

    // Create prescriptions
    cms.createPrescription(1, 1, "2025-09-15", "Take after meals", {1});
    cms.createPrescription(1, 2, "2025-09-17", "Take twice daily", {3});
    cms.createPrescription(3, 2, "2025-09-18", "Take once daily", {4});

    // Generate bills 
    cms.generateBill(1, 20.0, "2025-09-15");
    cms.generateBill(2, 25.0, "2025-09-17");
    cms.generateBill(3, 30.0, "2025-09-18");

}

// Simple menu-driven interface for testing
void runMenu(ClinicManagementSystem& cms) {
    int choice;

    do {
        cout << "\n=== CLINIC MANAGEMENT MENU ===" << endl;
        cout << "1.  Add Patient\n2.  Add Doctor\n3.  Schedule Appointment\n4.  Reschedule Appointment\n";
        cout << "5.  Complete Appointment\n6.  Cancel Appointment\n7.  Create Prescription\n8.  Generate Bill\n";
        cout << "9.  Show All Medicines\n10. Show All Appointments\n";
        cout << "11. Find Patient by ID\n12. Find Doctor by ID\n";
        cout << "13. Show All Patients\n14. Show All Doctors\n15. Show All Prescriptions\n16. Show All Bills\n";
        cout << "0.  Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int type;
                cout << "Choose patient type:\n1. Regular\n2. Chronic\nEnter choice: ";
                cin >> type;

                string name;
                int age;
                cout << "Enter patient name: ";
                cin.ignore(); getline(cin, name);
                cout << "Enter age: ";
                cin >> age;

                if (type == 1) {
                    cms.addPatient(name, age);
                } else if (type == 2) {
                    string condition, lastCheckup;
                    cout << "Enter chronic condition: ";
                    cin.ignore(); getline(cin, condition);
                    cout << "Enter last checkup date (YYYY-MM-DD): ";
                    getline(cin, lastCheckup);
                    cms.addChronicPatient(name, age, condition, lastCheckup);
                } else {
                    cout << "Invalid patient type selected." << endl;
                }
                break;
            }
            case 2: {
                string name, specialty;
                cout << "Enter doctor name: ";
                cin.ignore(); getline(cin, name);
                cout << "Enter specialty: ";
                getline(cin, specialty);
                cms.addDoctor(name, specialty);
                break;
            }
            case 3: {
                string date, time, reason;
                int pid, did;
                cout << "Enter date (YYYY-MM-DD): "; cin >> date;
                cout << "Enter time (HH:MM): "; cin >> time;
                cout << "Enter reason: "; cin.ignore(); getline(cin, reason);
                cout << "Enter patient ID: "; cin >> pid;
                cout << "Enter doctor ID: "; cin >> did;
                cms.scheduleAppointment(date, time, reason, pid, did);
                break;
            }
            case 4: {
                int aid;
                string newDate, newTime;
                cout << "Enter appointment ID: "; cin >> aid;
                cout << "New date (YYYY-MM-DD): "; cin >> newDate;
                cout << "New time (HH:MM): "; cin >> newTime;
                cms.rescheduleAppointment(aid, newDate, newTime);
                break;
            }
            case 5: {
                int aid;
                string record;
                cout << "Enter appointment ID: "; cin >> aid;
                cout << "Treatment record: "; cin.ignore(); getline(cin, record);
                cms.completeAppointment(aid, record);
                break;
            }
            case 6: {
                int aid;
                cout << "Enter appointment ID: "; cin >> aid;
                cms.cancelAppointment(aid);
                break;
            }
            case 7: {
                int pid, did;
                string date, instructions;
                vector<int> medIDs;

                cout << "Enter patient ID: "; cin >> pid;
                cout << "Enter doctor ID: "; cin >> did;
                cout << "Enter prescription date (YYYY-MM-DD): "; cin >> date;
                cout << "Enter instructions: "; cin.ignore(); getline(cin, instructions);

                // Display available medicines
                cout << "\n=== AVAILABLE MEDICINES ===" << endl;
                const vector<Medicine>& meds = cms.getMedicineInventory(); // Bạn cần thêm getter này
                for (size_t i = 0; i < meds.size(); ++i) {
                    cout << "ID: " << i + 1 << " | " << meds[i].getName() << " - $" << meds[i].getPrice() << endl;
                }

                // Select medicines
                cout << "\nEnter medicine IDs to prescribe (end with -1): ";
                int id;
                while (cin >> id && id != -1) {
                    medIDs.push_back(id);
                }
                cms.createPrescription(pid, did, date, instructions, medIDs);
                break;
            }
            case 8: {
                int presID;
                double fee;
                string date;

                cout << "Enter Prescription ID: ";
                cin >> presID;

                cout << "Enter Consultation Fee: $";
                cin >> fee;

                cout << "Enter Bill Date (YYYY-MM-DD): ";
                cin >> date;

                cms.generateBill(presID, fee, date);
                break;
            }
            case 9: cms.displayAllMedicines(); break;
            case 10: cms.displayAllAppointments(); break;
            case 11: {
                int pid;
                cout << "Enter patient ID to find: ";
                cin >> pid;
                Patient* p = cms.findPatient(pid);
                if (p) {
                    cout << "\n=== PATIENT FOUND ===" << endl;
                    p->displayInfo();
                } else {
                    cout << "Patient not found." << endl;
                }
                break;
            }
            case 12: {
                int did;
                cout << "Enter doctor ID to find: ";
                cin >> did;
                Doctor* d = cms.findDoctor(did);
                if (d) {
                    cout << "\n=== DOCTOR FOUND ===" << endl;
                    d->displayInfo();
                } else {
                    cout << "Doctor not found." << endl;
                }
                break;
            }
            case 13: cms.displayAllPatients(); break;
            case 14: cms.displayAllDoctors(); break;
            case 15: cms.displayAllPrescriptions(); break;
            case 16: cms.displayAllBills(); break;
            case 0: cout << "Exiting system. Goodbye!" << endl; break;
            default: cout << "Invalid choice. Try again." << endl;
        }

    } while (choice != 0);
}

int main() {
    ClinicManagementSystem cms;
    initializeSampleData(cms);
    runMenu(cms);             
    return 0;
}
