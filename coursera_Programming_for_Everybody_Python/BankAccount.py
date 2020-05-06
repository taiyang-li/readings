#!/usr/local/bin/python
class BankAccount:
    def __init__(self, initial_balance):
        """Creates an account with the given balance."""
        self._balance = initial_balance
        self._fee = 0
        
    
    def deposit(self, amount):
        """Deposits the amount into the account."""
        self._balance = self._balance + amount

    def withdraw(self, amount):
        """
        Withdraws the amount from the account.  Each withdrawal resulting in a
        negative balance also deducts a penalty fee of 5 dollars from the balance.
        """
        self._balance = self._balance - amount
        if self._balance < 0:
            self._balance = self._balance - 5
            self._fee = self._fee + 5

    def get_balance(self):
        """Returns the current balance in the account."""
        return self._balance 

    def get_fees(self):
        """Returns the total fees ever deducted from the account."""
        return self._fee
