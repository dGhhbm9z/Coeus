DROP DATABASE IF EXISTS `com_coeus`;
CREATE DATABASE IF NOT EXISTS `com_coeus` /*!40100 DEFAULT CHARACTER SET utf8 */;
USE `com_coeus`;


CREATE TABLE IF NOT EXISTS `companies` (
  `VAT` varchar(30) NOT NULL,
  `IRS` varchar(100) NOT NULL,
  `CompanyName` varchar(255) NOT NULL,
  `LegalInc` varchar(255) NOT NULL,
  `Address` varchar(255) NOT NULL,
  `AddressNumber` varchar(255) NOT NULL,
  `PersonInCharge` varchar(255) NOT NULL,
  `Telephone` varchar(255) NOT NULL,
  `Activity` varchar(255) NOT NULL,
  `StartDate` date NOT NULL,
  `Comments` text,
  PRIMARY KEY (`VAT`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

CREATE TABLE IF NOT EXISTS `accounts` (
  `VAT` varchar(30) NOT NULL,
  `Code` varchar(30) NOT NULL,
  `Name` varchar(100) NOT NULL,
  `ShortName` varchar(10) NOT NULL,
  `AccountType` varchar(255) NOT NULL,
  `XreosPist` varchar(255) NOT NULL,
  PRIMARY KEY (`VAT`,`Code`),
  CONSTRAINT `accounts_ibfk_1` FOREIGN KEY (`VAT`) REFERENCES `companies` (`VAT`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

CREATE TABLE IF NOT EXISTS `customers` (
  `CustomerCode` varchar(20) NOT NULL,
  `CompanyVAT` varchar(10) NOT NULL,
  `CustomerVAT` varchar(10) NOT NULL,
  `Trademark` varchar(50) NOT NULL,
  `Name` varchar(30) NOT NULL,
  `FathersName` varchar(15) NOT NULL,
  `DateOfBirth` date NOT NULL,
  `Address` varchar(50) NOT NULL,
  `City` varchar(20) NOT NULL,
  `Country` varchar(20) NOT NULL,
  `ShippingAdress` varchar(60) NOT NULL,
  `Phonenumber` varchar(20) NOT NULL,
  `Faxnumber` varchar(20) NOT NULL,
  `Email` varchar(30) NOT NULL,
  `IDcardNumber` varchar(10) NOT NULL,
  `CustomerTransactions` varchar(255) NOT NULL,
  `PublicRevenueService` varchar(50) NOT NULL,
  `CommercialActivity` varchar(255) NOT NULL,
  PRIMARY KEY (`CustomerCode`,`CustomerVAT`),
  KEY `CompanyVAT` (`CompanyVAT`),
  CONSTRAINT `customers_ibfk_1` FOREIGN KEY (`CompanyVAT`) REFERENCES `companies` (`VAT`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;


CREATE TABLE IF NOT EXISTS `events` (
  `VAT` varchar(30) NOT NULL,
  `Invoice` varchar(100) NOT NULL,
  `RecordDate` date NOT NULL,
  `RecordType` date NOT NULL,
  `Comments` varchar(255) NOT NULL,
  `Reasoning` varchar(255) NOT NULL,
  PRIMARY KEY (`VAT`,`Invoice`),
  CONSTRAINT `events_ibfk_1` FOREIGN KEY (`VAT`) REFERENCES `companies` (`VAT`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;


CREATE TABLE IF NOT EXISTS `events2accounts` (
  `VAT` varchar(30) NOT NULL,
  `Code` varchar(30) NOT NULL,
  `Invoice` varchar(100) NOT NULL,
  `EventType` varchar(255) NOT NULL,
  `Amount` decimal(10,4) NOT NULL,
  PRIMARY KEY (`VAT`,`Code`,`Invoice`),
  KEY `VAT` (`VAT`,`Invoice`),
  CONSTRAINT `events2accounts_ibfk_1` FOREIGN KEY (`VAT`, `Code`) REFERENCES `accounts` (`VAT`, `Code`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `events2accounts_ibfk_2` FOREIGN KEY (`VAT`, `Invoice`) REFERENCES `events` (`VAT`, `Invoice`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;


CREATE TABLE IF NOT EXISTS `personel` (
  `CompanyVAT` varchar(30) NOT NULL,
  `Code` varchar(30) NOT NULL,
  `PersonalVAT` varchar(30) NOT NULL,
  `IRS` varchar(100) NOT NULL,
  `Name` varchar(255) NOT NULL,
  `FathersName` varchar(255) NOT NULL,
  `MothersName` varchar(255) NOT NULL,
  `ADT` varchar(255) NOT NULL,
  `Address` varchar(255) NOT NULL,
  `AddressNumber` varchar(255) NOT NULL,
  `Telephone` varchar(255) NOT NULL,
  `BirthDate` date NOT NULL,
  `Insured` varchar(255) NOT NULL,
  `NumberOfChildern` varchar(255) NOT NULL,
  `IKA` varchar(255) NOT NULL,
  `SSN` varchar(255) NOT NULL,
  `Experience` varchar(255) NOT NULL,
  `Amount` decimal(10,4) NOT NULL,
  `Department` varchar(255) NOT NULL,
  PRIMARY KEY (`CompanyVAT`,`Code`,`PersonalVAT`),
  CONSTRAINT `personel_ibfk_1` FOREIGN KEY (`CompanyVAT`, `Code`) REFERENCES `accounts` (`VAT`, `Code`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

CREATE TABLE IF NOT EXISTS `suppliers` (
  `SupplierCode` varchar(20) NOT NULL,
  `CompanyVAT` varchar(10) NOT NULL,
  `SupplierVAT` varchar(10) NOT NULL,
  `Trademark` varchar(50) NOT NULL,
  `Name` varchar(30) NOT NULL,
  `FathersName` varchar(15) NOT NULL,
  `DateOfBirth` date NOT NULL,
  `Address` varchar(50) NOT NULL,
  `City` varchar(20) NOT NULL,
  `Country` varchar(20) NOT NULL,
  `PhoneNumber` varchar(20) NOT NULL,
  `FaxNumber` varchar(20) NOT NULL,
  `Email` varchar(30) NOT NULL,
  `IDcardNumber` varchar(10) NOT NULL,
  `SupplierTransactions` varchar(255) NOT NULL,
  `PublicRevenueService` varchar(50) NOT NULL,
  `CommercialActivity` varchar(255) NOT NULL,
  PRIMARY KEY (`SupplierCode`,`SupplierVAT`),
  KEY `CompanyVAT` (`CompanyVAT`),
  CONSTRAINT `suppliers_ibfk_1` FOREIGN KEY (`CompanyVAT`) REFERENCES `companies` (`VAT`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
