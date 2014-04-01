DROP DATABASE IF EXISTS COM_COEUS;
CREATE DATABASE COM_COEUS;
USE COM_COEUS;

CREATE TABLE Companies
(
VAT varchar(30) NOT NULL,
IRS varchar(100) NOT NULL,
CompanyName varchar(255) NOT NULL,
LegalInc varchar(255) NOT NULL,
Address varchar(255) NOT NULL,
AddressNumber varchar(255) NOT NULL,
PersonInCharge varchar(255) NOT NULL,
Telephone varchar(255) NOT NULL,
Activity varchar(255) NOT NULL,
StartDate Date NOT NULL,
Comments Text,
PRIMARY KEY (VAT)
) ENGINE=InnoDB;

CREATE TABLE Accounts
(
VAT varchar(30) NOT NULL,
Code varchar(30) NOT NULL,
Name varchar(100) NOT NULL,
ShortName varchar(10) NOT NULL,
AccountType varchar(255) NOT NULL,
Amount DECIMAL(10,4) NOT NULL,
Remainder DECIMAL(10,4) NOT NULL,
PRIMARY KEY (VAT, Code),
FOREIGN KEY (VAT) REFERENCES Companies(VAT) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB;

CREATE TABLE Events
(
VAT varchar(30) NOT NULL,
Invoice varchar(100) NOT NULL,
Id varchar(255) NOT NULL,
RecordDate Date NOT NULL,
RecordType Date NOT NULL,
Comments varchar(255) NOT NULL,
Reasoning varchar(255) NOT NULL,
PRIMARY KEY (VAT, Invoice),
FOREIGN KEY (VAT) REFERENCES Companies(VAT) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB;

CREATE TABLE Events2Accounts
(
VAT varchar(30) NOT NULL,
Code varchar(30) NOT NULL,
Invoice varchar(100) NOT NULL,
EventType varchar(255) NOT NULL,
Amount DECIMAL(10,4) NOT NULL,
FOREIGN KEY (VAT, Code) REFERENCES Accounts(VAT, Code) ON DELETE CASCADE ON UPDATE CASCADE,
FOREIGN KEY (VAT, Invoice) REFERENCES Events(VAT, Invoice) ON DELETE CASCADE ON UPDATE CASCADE,
PRIMARY KEY (VAT, Code, Invoice)
) ENGINE=InnoDB;

CREATE TABLE Personel
(
CompanyVAT varchar(30) NOT NULL,
Code varchar(30) NOT NULL,
PersonalVAT varchar(30) NOT NULL,
IRS varchar(100) NOT NULL,
Name varchar(255) NOT NULL,
FathersName varchar(255) NOT NULL,
MothersName varchar(255) NOT NULL,
ADT varchar(255) NOT NULL,
Address varchar(255) NOT NULL,
AddressNumber varchar(255) NOT NULL,
Telephone varchar(255) NOT NULL,
BirthDate Date NOT NULL,
Insured varchar(255) NOT NULL,
NumberOfChildern varchar(255) NOT NULL,
IKA varchar(255) NOT NULL,
SSN varchar(255) NOT NULL,
Experience varchar(255) NOT NULL,
Amount DECIMAL(10,4) NOT NULL,
Department varchar(255) NOT NULL,
PRIMARY KEY (CompanyVAT, Code, PersonalVAT),
FOREIGN KEY (CompanyVAT, Code) REFERENCES Accounts(VAT, Code) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB;

CREATE TABLE Customers
(
CustomerCode varchar(20) NOT NULL,
CompanyVAT varchar(10) NOT NULL,
CustomerVAT varchar(10) NOT NULL,
Trademark varchar(50) NOT NULL,
Name varchar(30) NOT NULL,
FathersName varchar(15) NOT NULL,
DateOfBirth Date NOT NULL,
Address varchar(50) NOT NULL,
City varchar(20) NOT NULL,
Country varchar(20) NOT NULL,
ShippingAdress varchar(60) NOT NULL,
Phonenumber varchar(20) NOT NULL,
Faxnumber varchar(20) NOT NULL,
Email varchar(30) NOT NULL,
IDcardNumber varchar(10) NOT NULL,
CustomerTransactions varchar(255) NOT NULL,
PublicRevenueService varchar(50) NOT NULL,
CommercialActivity varchar(255) NOT NULL,
PRIMARY KEY (CustomerCode, CustomerVAT),
FOREIGN KEY (CompanyVAT) REFERENCES Companies(VAT) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB;

Create TABLE Suppliers
(
SupplierCode varchar(20) NOT NULL,
CompanyVAT varchar (10) NOT NULL,
SupplierVAT varchar(10) NOT NULL,
Trademark varchar(50) NOT NULL,
Name varchar(30) NOT NULL,
FathersName varchar(15) NOT NULL,
DateOfBirth DATE NOT NULL,
Address varchar(50) NOT NULL,
City varchar(20) NOT NULL,
Country varchar(20) NOT NULL,
PhoneNumber varchar(20) NOT NULL,
FaxNumber varchar(20) NOT NULL,
Email varchar(30) NOT NULL,
IDcardNumber varchar(10) NOT NULL,
SupplierTransactions varchar(255) NOT NULL,
PublicRevenueService varchar(50) NOT NULL,
CommercialActivity varchar(255) NOT NULL,
PRIMARY KEY (SupplierCode, SupplierVAT),
FOREIGN KEY (CompanyVAT) REFERENCES Companies(VAT) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB;
