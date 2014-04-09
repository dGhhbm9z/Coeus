-- --------------------------------------------------------
-- Host:                         127.0.0.1
-- Server version:               5.5.36-MariaDB - mariadb.org binary distribution
-- Server OS:                    Win64
-- HeidiSQL Version:             8.0.0.4396
-- --------------------------------------------------------

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;

-- Dumping database structure for com_coeus
DROP DATABASE IF EXISTS `com_coeus`;
CREATE DATABASE IF NOT EXISTS `com_coeus` /*!40100 DEFAULT CHARACTER SET latin1 */;
USE `com_coeus`;


-- Dumping structure for table com_coeus.accounts
DROP TABLE IF EXISTS `accounts`;
CREATE TABLE IF NOT EXISTS `accounts` (
  `VAT` varchar(30) NOT NULL,
  `Code` varchar(30) NOT NULL,
  `Name` varchar(100) NOT NULL,
  `ShortName` varchar(10) NOT NULL,
  `AccountType` varchar(255) NOT NULL,
  `XreosPist` varchar(255) NOT NULL,
  PRIMARY KEY (`VAT`,`Code`),
  CONSTRAINT `accounts_ibfk_1` FOREIGN KEY (`VAT`) REFERENCES `companies` (`VAT`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- Data exporting was unselected.


-- Dumping structure for table com_coeus.companies
DROP TABLE IF EXISTS `companies`;
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
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- Data exporting was unselected.


-- Dumping structure for table com_coeus.customers
DROP TABLE IF EXISTS `customers`;
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
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- Data exporting was unselected.


-- Dumping structure for table com_coeus.events
DROP TABLE IF EXISTS `events`;
CREATE TABLE IF NOT EXISTS `events` (
  `VAT` varchar(30) NOT NULL,
  `Invoice` varchar(100) NOT NULL,
  `RecordDate` date NOT NULL,
  `RecordType` date NOT NULL,
  `Comments` varchar(255) NOT NULL,
  `Reasoning` varchar(255) NOT NULL,
  PRIMARY KEY (`VAT`,`Invoice`),
  CONSTRAINT `events_ibfk_1` FOREIGN KEY (`VAT`) REFERENCES `companies` (`VAT`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- Data exporting was unselected.


-- Dumping structure for table com_coeus.events2accounts
DROP TABLE IF EXISTS `events2accounts`;
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
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- Data exporting was unselected.


-- Dumping structure for table com_coeus.personel
DROP TABLE IF EXISTS `personel`;
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
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- Data exporting was unselected.


-- Dumping structure for table com_coeus.suppliers
DROP TABLE IF EXISTS `suppliers`;
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
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- Data exporting was unselected.
/*!40101 SET SQL_MODE=IFNULL(@OLD_SQL_MODE, '') */;
/*!40014 SET FOREIGN_KEY_CHECKS=IF(@OLD_FOREIGN_KEY_CHECKS IS NULL, 1, @OLD_FOREIGN_KEY_CHECKS) */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
