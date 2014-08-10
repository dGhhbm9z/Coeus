-- --------------------------------------------------------
-- Host:                         127.0.0.1
-- Server version:               5.5.36-MariaDB - mariadb.org binary distribution
-- Server OS:                    Win64
-- HeidiSQL Version:             8.3.0.4694
-- --------------------------------------------------------

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;

-- Dumping database structure for com_coeus
CREATE DATABASE IF NOT EXISTS `com_coeus` /*!40100 DEFAULT CHARACTER SET latin1 */;
USE `com_coeus`;


-- Dumping structure for table com_coeus.accounts
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

-- Dumping data for table com_coeus.accounts: ~6 rows (approximately)
/*!40000 ALTER TABLE `accounts` DISABLE KEYS */;
INSERT INTO `accounts` (`VAT`, `Code`, `Name`, `ShortName`, `AccountType`, `XreosPist`) VALUES
	('0123456789', '20.00.00', 'Fortigo', 'For', 'xreostikos\r\n', 'x'),
	('0123456789', '38.00.00', 'Tameio', 't', 'xreostikos\\', 'x'),
	('0123456789', '40', 'promitheytes', 'oti', 'oti ', 'x'),
	('0123456789', '40.00', 'promitheutes eswter', 'oti', 'oti ', 'x'),
	('0123456789', '40.00.00', 'Promitheytes eswterikou', 'Pels', 'xreostikos', 'x'),
	('0123456789', '40.00.00.01', 'promitheutis antwniou b', 'oti ', 'oti', 'x');
/*!40000 ALTER TABLE `accounts` ENABLE KEYS */;


-- Dumping structure for table com_coeus.companies
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

-- Dumping data for table com_coeus.companies: ~2 rows (approximately)
/*!40000 ALTER TABLE `companies` DISABLE KEYS */;
INSERT INTO `companies` (`VAT`, `IRS`, `CompanyName`, `LegalInc`, `Address`, `AddressNumber`, `PersonInCharge`, `Telephone`, `Activity`, `StartDate`, `Comments`) VALUES
	('0123456789', 'amar', 'asd', 'epe', 'argonaut', '50', 'asdgf', '98765412631', 'soft dev', '2011-04-06', 'ggqqdel'),
	('123654789', 'Amarousiou', 'Brewing Octopus', 'AE', 'Argonauton', '50', 'Augoustinos Evripiotis', '6977710996', 'Brewing', '2013-01-01', '0');
/*!40000 ALTER TABLE `companies` ENABLE KEYS */;


-- Dumping structure for table com_coeus.customers
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

-- Dumping data for table com_coeus.customers: ~2 rows (approximately)
/*!40000 ALTER TABLE `customers` DISABLE KEYS */;
INSERT INTO `customers` (`CustomerCode`, `CompanyVAT`, `CustomerVAT`, `Trademark`, `Name`, `FathersName`, `DateOfBirth`, `Address`, `City`, `Country`, `ShippingAdress`, `Phonenumber`, `Faxnumber`, `Email`, `IDcardNumber`, `CustomerTransactions`, `PublicRevenueService`, `CommercialActivity`) VALUES
	('30.00.01', '123654789', '032185245', '0', 'Ioannis Skenderoglou', 'Vasileios', '1989-05-19', 'Gounari 13', 'Patra', 'Greece', 'Gounari 13, Patra, Greece', '6980025852', '0', 'gsken@gmail.com', 'x987456', '0', 'asd', '0'),
	('30.00.02', '123654789', '753951846', '0', 'Alexander Hopko', 'Marek', '1986-08-08', 'koszykowa 143', 'warsaw', 'Poland', 'koszykowa 132, warsaw, Poland', '0048503215978', '0', 'alekhop@gmail.com', '7348956', '500', 'asd', '0');
/*!40000 ALTER TABLE `customers` ENABLE KEYS */;


-- Dumping structure for table com_coeus.events
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

-- Dumping data for table com_coeus.events: ~3 rows (approximately)
/*!40000 ALTER TABLE `events` DISABLE KEYS */;
INSERT INTO `events` (`VAT`, `Invoice`, `RecordDate`, `RecordType`, `Comments`, `Reasoning`) VALUES
	('0123456789', '38.00.00', '2014-04-06', '2014-04-06', 'xcv', 'xcv'),
	('0123456789', 'AP 1645', '2014-04-06', '2014-04-06', 'a', 'a'),
	('0123456789', 'DA 1533', '2013-04-06', '2013-04-06', 'asd', 'asd');
/*!40000 ALTER TABLE `events` ENABLE KEYS */;


-- Dumping structure for table com_coeus.events2accounts
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

-- Dumping data for table com_coeus.events2accounts: ~5 rows (approximately)
/*!40000 ALTER TABLE `events2accounts` DISABLE KEYS */;
INSERT INTO `events2accounts` (`VAT`, `Code`, `Invoice`, `EventType`, `Amount`) VALUES
	('0123456789', '20.00.00', 'DA 1533', 'xreosi', 2500.0000),
	('0123456789', '38.00.00', '38.00.00', 'xreosi', 10000.0000),
	('0123456789', '38.00.00', 'AP 1645', 'pistosi', 2500.0000),
	('0123456789', '40.00.00', 'AP 1645', 'xreosi', 2500.0000),
	('0123456789', '40.00.00', 'DA 1533', 'pistosi', 2500.0000);
/*!40000 ALTER TABLE `events2accounts` ENABLE KEYS */;


-- Dumping structure for table com_coeus.personel
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

-- Dumping data for table com_coeus.personel: ~0 rows (approximately)
/*!40000 ALTER TABLE `personel` DISABLE KEYS */;
/*!40000 ALTER TABLE `personel` ENABLE KEYS */;


-- Dumping structure for table com_coeus.suppliers
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

-- Dumping data for table com_coeus.suppliers: ~3 rows (approximately)
/*!40000 ALTER TABLE `suppliers` DISABLE KEYS */;
INSERT INTO `suppliers` (`SupplierCode`, `CompanyVAT`, `SupplierVAT`, `Trademark`, `Name`, `FathersName`, `DateOfBirth`, `Address`, `City`, `Country`, `PhoneNumber`, `FaxNumber`, `Email`, `IDcardNumber`, `SupplierTransactions`, `PublicRevenueService`, `CommercialActivity`) VALUES
	('50.00.01', '123654789', '112233445', 'Malt AE', 'George Eustathiou', 'Nick', '1977-08-08', 'Trikoupi 24', 'Athens', 'Greece', '6982541675', '2105889367', 'georgeu@gmail.com', 'x875598', '1000', 'asd', 'Malt Wholesale'),
	('50.00.02', '123654789', '922114455', 'Yeast AE', 'Manolis Nikolopoulos', 'Ioannis', '1990-05-03', 'Ethnikis Antistaseos 53', 'Athens', 'Greece', '6981374781', '2108064330', 'mnikol@yahoo.com', 'x541136', '5000', 'asd', 'Yeast Wholesale'),
	('50.00.03', '123654789', '08754899', 'Boiler AE', 'Xaris Polemitis', 'George', '1989-06-19', 'Diomidous 10', 'Athens', 'Greece', '6974504224', '2106139014', 'xarpol@hotmail.com', 'x556621', '0', 'asd', 'Brewing Equipment Sales');
/*!40000 ALTER TABLE `suppliers` ENABLE KEYS */;
/*!40101 SET SQL_MODE=IFNULL(@OLD_SQL_MODE, '') */;
/*!40014 SET FOREIGN_KEY_CHECKS=IF(@OLD_FOREIGN_KEY_CHECKS IS NULL, 1, @OLD_FOREIGN_KEY_CHECKS) */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
