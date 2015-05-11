#Как запустить:1. Скачать драйвера для подключения к MySQL (качайте для С, и скорее всего для Win32)2. Указать путь к include3. Указать путь к lib (в lib нужно достать библиотеку mysqlclient.lib из папки VS12 (или другой,  в зависимости от версии Visual Studio), и положить на уровень шыше)4. указать линковщику библиотеки libmysql.lib и mysqlclient.lib5. Положить dll, чтобы его могла найти программа6. Проверьте или запущена служба mysql (mysqld.exe)7. Проверьте или создайте БД (testdb с таблицами test_table1 test_table2) заполните данными### Для генерации тестовой БД можно использовать скрипт:```SQLSET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='TRADITIONAL,ALLOW_INVALID_DATES';
CREATE SCHEMA IF NOT EXISTS `testdb` DEFAULT CHARACTER SET latin1 ;
USE `testdb` ;-- ------------------------------------------------------- Table `testdb`.`test_table1`-- -----------------------------------------------------CREATE  TABLE IF NOT EXISTS `testdb`.`test_table1` (  `ID` INT(11) NOT NULL AUTO_INCREMENT ,  `Text` VARCHAR(45) NULL DEFAULT NULL ,  PRIMARY KEY (`ID`) )ENGINE = InnoDBAUTO_INCREMENT = 3DEFAULT CHARACTER SET = latin1;
-- ------------------------------------------------------- Table `testdb`.`test_table2`-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `testdb`.`test_table2` (  `ID` INT(11) NOT NULL AUTO_INCREMENT ,  `Text` VARCHAR(45) NULL DEFAULT NULL ,  PRIMARY KEY (`ID`) )ENGINE = InnoDBAUTO_INCREMENT = 2DEFAULT CHARACTER SET = latin1;
USE `testdb` ;SET SQL_MODE=@OLD_SQL_MODE;SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;
USE `testdb` ;
INSERT INTO `testdb`.`test_table1` (`Text`) VALUES ('data table1');
INSERT INTO `testdb`.`test_table2` (`Text`) VALUES ('data table2');
```
