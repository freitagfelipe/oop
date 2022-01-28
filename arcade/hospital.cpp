#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include "auxiliar.hpp"

class IPatient;

class IDoctor {
public:
    virtual ~IDoctor() {}
    virtual void add_patient(IPatient*) = 0;
    virtual std::string get_specialization() const = 0;
    virtual std::string get_name() const = 0;
    virtual const std::map<std::string, IPatient*>& get_patients() const = 0;
    virtual void remove_patient(const std::string&) = 0;
};

class IPatient {
public:
    virtual ~IPatient() {}
    virtual void add_doctor(IDoctor*) = 0;
    virtual std::string get_diagnostic() const = 0;
    virtual std::string get_name() const = 0;
    virtual const std::map<std::string, IDoctor*>& get_doctors() const = 0;
    virtual void remove_doctor(const std::string&) = 0;
};

class Doctor : public IDoctor {
public:
    Doctor(const std::string &name, const std::string &specialization) : name(name), specialization(specialization) {}

    void add_patient(IPatient *new_patient) override {
        std::map<std::string, IPatient*>::iterator it {this->patients.find(new_patient->get_name())};

        if (it != this->patients.end()) {
            return;
        }

        try {
            new_patient->add_doctor(this);
            this->patients.insert({new_patient->get_name(), new_patient});
        } catch(const std::string &e) {
            std::cout << e << std::endl;
        }
    }

    void remove_patient(const std::string &name) override {
        std::map<std::string, IPatient*>::iterator it {this->patients.find(name)};

        if (it != this->patients.end()) {
            IPatient *patient {it->second};

            this->patients.erase(it);

            patient->remove_doctor(this->name);
        }
    }

    std::string get_specialization() const override {
        return this->specialization;
    }

    std::string get_name() const override {
        return this->name;
    }

    const std::map<std::string, IPatient*>& get_patients() const override {
        return this->patients;
    }

    friend std::ostream& operator<<(std::ostream &os, const Doctor &doctor) {
        os << doctor.name << ":" << doctor.specialization << "\n\t↳Patients: [";

        int count {0};

        for (auto &[name, patient] : doctor.patients) {
            if (count++ > 0) {
                os << ", ";
            }

            os << name;
        }

        os << "]";

        return os;
    }

private:
    std::string name;
    std::string specialization;
    std::map<std::string, IPatient*> patients;
};

class Patient : public IPatient {
public:
    Patient(const std::string &name, const std::string &diagnostic) : name(name), diagnostic(diagnostic) {}

    void add_doctor(IDoctor* new_doctor) override {
        std::map<std::string, IDoctor*>::iterator it {this->doctors.find(new_doctor->get_name())};

        if (it != this->doctors.end()) {
            return;
        }

        for (auto &[name, doctor] : this->doctors) {
            if (doctor->get_specialization() == new_doctor->get_specialization()) {
                throw std::string("Error: you already have a doctor with the same specialization!");
            }
        }

        this->doctors.insert({new_doctor->get_name(), new_doctor});

        new_doctor->add_patient(this);
    }

    void remove_doctor(const std::string &name) override {
        std::map<std::string, IDoctor*>::iterator it {this->doctors.find(name)};

        if (it != this->doctors.end()) {
            IDoctor *doctor {it->second};

            this->doctors.erase(it);

            doctor->remove_patient(this->name);
        }
    }

    std::string get_diagnostic() const override {
        return this->diagnostic;
    }

    std::string get_name() const override {
        return this->name;
    }

    const std::map<std::string, IDoctor*>& get_doctors() const override {
        return this->doctors;
    }

    friend std::ostream& operator<<(std::ostream &os, const Patient &patient) {
        os << patient.name << ":" << patient.diagnostic << "\n\t↳Doctors: [";

        int count {0};

        for (auto &[name, doctor] : patient.doctors) {
            if (count++ > 0) {
                os << ", ";
            }

            os << name;
        }

        os << "]";

        return os;
    }
    
private:
    std::string name;
    std::string diagnostic;
    std::map<std::string, IDoctor*> doctors;
};

class Hospital {
public:
    Hospital() = default;

    ~Hospital() {
        for (auto &[name, doctor] : this->doctors) {
            delete doctor;
        }

        for (auto &[name, patient] : this->patients) {
            delete patient;
        }
    }

    void add_doctor(IDoctor *doctor) {
        auto &&[it, added] {this->doctors.insert({doctor->get_name(), doctor})};

        if (!added) {
            delete doctor;
        }
    }

    void add_patient(IPatient *patient) {
        auto &&[it, added] {this->patients.insert({patient->get_name(), patient})};

        if (!added) {
            delete patient;
        }
    }

    void tie(const std::string &doctor_name, const std::string &patient_name) {
        std::map<std::string, IDoctor*>::iterator doctor_it {this->doctors.find(doctor_name)};
        std::map<std::string, IPatient*>::iterator patient_it {this->patients.find(patient_name)};

        if (doctor_it == this->doctors.end()) {
            throw std::string("Error: doctor not found!");
        } else if (patient_it == this->patients.end()) {
            throw std::string("Error: patient " + patient_name + " not found!");
        }

        try {
            doctor_it->second->add_patient(patient_it->second);
        } catch (const std::string &e) {
            std::cout << e << std::endl;
        }
        
    }

    void remove_doctor(const std::string &name) {
        std::map<std::string, IDoctor*>::iterator it {this->doctors.find(name)};

        if (it == this->doctors.end()) {
            throw std::string("Error: doctor not found!");
        }

        std::vector<IPatient*> patients_to_remove;

        for (auto &[patient_name, patient] : it->second->get_patients()) {
            patients_to_remove.push_back(patient);
        }

        for (IPatient *patient : patients_to_remove) {
            patient->remove_doctor(name);
        }

        delete it->second;

        this->doctors.erase(it);
    }

    void remove_patient(const std::string &name) {
        std::map<std::string, IPatient*>::iterator it {this->patients.find(name)};

        if (it == this->patients.end()) {
            throw std::string("Error: patient not found!");
        }

        std::vector<IDoctor*> doctors_to_remove;

        for (auto &[doctor_name, doctor] : it->second->get_doctors()) {
            doctors_to_remove.push_back(doctor);
        }

        for (IDoctor *doctor : doctors_to_remove) {
            doctor->remove_patient(name);
        }

        delete it->second;

        this->patients.erase(it);
    }

    friend std::ostream& operator<<(std::ostream &os, const Hospital &hospital) {
        for (auto &[name, patient] : hospital.patients) {
            os << "Patient: " << *static_cast<Patient*>(patient) << std::endl;
        }

        int count {0};

        for (auto &[name, doctor] : hospital.doctors) {
            if (count++ > 0) {
                os << "\n";
            }

            os << "Doctor: " << *(static_cast<Doctor*>(doctor));
        }

        return os;
    }

private:
    std::map<std::string, IDoctor*> doctors;
    std::map<std::string, IPatient*> patients;
};

int main() {
    Hospital hospital;

    while (true) {
        std::cout << "$";

        std::vector<std::string> parameters {aux::get_cmd()};

        try {
            std::string cmd {parameters.at(0)};

            if (cmd == "end") {
                break;
            }

            std::vector<std::string> informations {aux::split(aux::join(aux::slice(parameters, 1), " "), ' ')};

            if (cmd != "show" && informations.size() == 0) {
                throw std::string("Error: bad command usage!");
            }
            
            if (cmd == "add-patients" || cmd == "addPacs") {
                for (std::string &information : informations) {
                    std::vector<std::string> patient_information {aux::split(information, '-')};

                    hospital.add_patient(new Patient(patient_information.at(0), patient_information.at(1)));
                }
            } else if (cmd == "add-doctors" || cmd == "addMeds") {
                for (std::string &information : informations) {
                    std::vector<std::string> doctor_information {aux::split(information, '-')};

                    hospital.add_doctor(new Doctor(doctor_information.at(0), doctor_information.at(1)));
                }
            } else if (cmd == "tie") {
                std::string doctor_name {informations.at(0)};

                for (std::string &patient_name : aux::slice(informations, 1)) {
                    hospital.tie(doctor_name, patient_name);
                }
            } else if (cmd == "show") {
                std::cout << hospital << std::endl;
            } else if (cmd == "remove-patient") {
                hospital.remove_patient(informations.at(0));
            } else if (cmd == "remove-doctor") {
                hospital.remove_doctor(informations.at(0));
            } else {
                std::cout << "Error: your command doesn't exist!" << std::endl;
            }
        } catch (const std::string &e) {
            std::cout << e << std::endl;
        } catch(const std::out_of_range &e) {
            std::cout << "Error: bad command usage!" << std::endl;
        }
    }

    return 0;
}