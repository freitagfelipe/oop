#include <iostream>
#include <vector>
#include <map>

class Account {
public:
    enum type {poupanca, corrente};

    Account(int id, std::string client_id, Account::type account_type) {
        this->id = id;
        this->client_id = client_id;
        this->account_type = account_type;
        this->balance = 0;
    }

    virtual ~Account() {}

    virtual void monthly_update() = 0;

    void deposit(double value) {
        if (value <= 0) {
            throw std::invalid_argument("O valor deve ser maior que 0");
        }

        this->balance += value;
    }

    void transfer(Account *destination_account, double value) {
        if (value > this->balance) {
            throw std::runtime_error("Saldo insuficiente");
        } else if (value <= 0) {
            throw std::invalid_argument("O valor deve ser maior que 0");
        }

        destination_account->balance += value;
        this->balance -= value;
    }

    void withdraw(double value) {
        if (value > this->balance) {
            throw std::runtime_error("Saldo insuficiente");
        } else if (value <= 0) {
            throw std::invalid_argument("O valor deve ser maior que 0");
        }

        this->balance -= value;
    }

    double get_balance() const {
        return this->balance;
    }

    std::string get_client_id() const {
        return this->client_id;
    }

    int get_id() const {
        return this->id;
    }

    Account::type get_account_type() const {
        return this->account_type;
    }

    friend std::ostream& operator<<(std::ostream &os, const Account &account) {
        os << account.id << ":" << account.client_id << ":" << account.balance << ":" << (account.account_type == Account::corrente ? "CC" : "CP");

        return os;
    }

protected:
    double balance;

private:
    int id;
    std::string client_id;
    Account::type account_type;
};

class SavingsAccount : public Account {
public:
    SavingsAccount(int id, std::string client_id) : Account(id, client_id, Account::poupanca) {}

    void monthly_update() override {
        this->balance += this->balance * 0.01;
    }

    friend std::ostream& operator<<(std::ostream &os, const SavingsAccount &saving_account) {
        const Account &account = saving_account;

        os << account;

        return os;
    }
};

class CheckingAccount : public Account {
public:
    CheckingAccount(int id, std::string client_id) : Account(id, client_id, Account::corrente) {}

    void monthly_update() override {
        this->balance -= 20;
    }

    friend std::ostream& operator<<(std::ostream &os, const CheckingAccount &checking_account) {
        const Account &account = checking_account;

        os << account;

        return os;
    }
};

class Client {
public:
    Client() {
        this->client_id = "";
    }

    Client(std::string client_id) {
        this->client_id = client_id;
    }

    void add_account(Account *account) {
        this->accounts.push_back(account);
    }

    std::vector<Account*>& get_accounts() {
        return this->accounts;
    }

    void set_accounts(std::vector<Account*> &accounts) {
        this->accounts = accounts;
    }

    std::string get_client_id() const {
        return this->client_id;
    }

    void set_client_id(std::string client_id) {
        this->client_id = client_id;
    }

    friend std::ostream& operator<<(std::ostream &os, const Client &client) {
        os << "- " << client.client_id << " [";

        int count {0};

        for (const Account *account : client.accounts) {
            if (count++ > 0) {
                os << ", ";
            }

            os << account->get_id();
        }

        os << "]";

        return os;
    }

private:
    std::vector<Account*> accounts;
    std::string client_id;
};

class BankAgency {
public:
    BankAgency() {
        this->next_account_id = 0;
    }
    
    ~BankAgency() {
        for (std::pair<const int, Account*> &pair : this->accounts) {
            delete pair.second;
        }
    }

    void add_client(std::string client_id) {
        Client new_client = Client(client_id);
        CheckingAccount *new_checking_account = new CheckingAccount(this->next_account_id++, client_id);
        SavingsAccount *new_saving_account = new SavingsAccount(this->next_account_id++, client_id);

        new_client.add_account(new_checking_account);
        new_client.add_account(new_saving_account);

        this->clients[client_id] = new_client;
        this->accounts[new_checking_account->get_id()] = new_checking_account;
        this->accounts[new_saving_account->get_id()] = new_saving_account;
    }

    void deposit(int account_id, double value) {
        if (this->accounts.find(account_id) == this->accounts.end()) {
            throw std::out_of_range("Id não encontrado");
        }

        try {
            this->accounts[account_id]->deposit(value);
        } catch (const std::invalid_argument &e) {
            std::cout << e.what() << std::endl;
        }
    }

    void monthly_update() {
        for (std::pair<const int, Account*> &pair : this->accounts) {
            pair.second->monthly_update();
        }
    }

    void transfer(int from_account_id, int for_account_id, double value) {
        if (this->accounts.find(from_account_id) == this->accounts.end()) {
            throw std::out_of_range("Id do remetente não encontrado");
        } else if (this->accounts.find(for_account_id) == this->accounts.end()) {
            throw std::out_of_range("Id do destinatário não encontrado");
        }

        try {
            this->accounts[from_account_id]->transfer(this->accounts[for_account_id], value);
        } catch (const std::runtime_error &e) {
            std::cout << e.what() << std::endl;
        } catch (const std::invalid_argument &e) {
            std::cout << e.what() << std::endl;
        }
    }

    void withdraw(int account_id, double value) {
        try {
            this->accounts[account_id]->withdraw(value);
        } catch (const std::runtime_error &e) {
            std::cout << e.what() << std::endl;
        } catch (const std::invalid_argument &e) {
            std::cout << e.what() << std::endl;
        }
    }

    friend std::ostream& operator<<(std::ostream &os, const BankAgency &bank_agency) {
        os << "Clients:\n";

        for (const std::pair<const std::string, Client> &pair : bank_agency.clients) {
            os << "\t" << pair.second << "\n";
        }

        os << "Accounts:\n";

        int count {0};

        for (const std::pair<const int, Account*> &pair : bank_agency.accounts) {
            if (count++ > 0) {
                os << "\n";
            }

            os << "\t" << *pair.second;
        }

        return os;
    }

private:
    std::map<std::string, Client> clients;
    std::map<int, Account*> accounts;
    int next_account_id;
};

int main() {

    return 0;
}