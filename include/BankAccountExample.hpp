
class BankAccount {

private:

  double balance;

public:

  BankAccount (double amount);

  BankAccount ();

  void deposit(double amount);

  void withdraw(double amount);

  double getBalance();
};
