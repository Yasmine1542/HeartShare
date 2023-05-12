+
--------------------------------------------------------
--  File created - Friday-April-28-2023   
--------------------------------------------------------
DROP TABLE "SYSTEM"."BENEVOLE";
--------------------------------------------------------
--  DDL for Table BENEVOLE
--------------------------------------------------------

  CREATE TABLE "SYSTEM"."BENEVOLE" 
   (	"ID" NUMBER, 
	"NOM" VARCHAR2(20 BYTE), 
	"MAIL" VARCHAR2(20 BYTE), 
	"DATENAISS" DATE, 
	"NUMTEL" NUMBER, 
	"ADRESSE" VARCHAR2(20 BYTE), 
	"DISPO" VARCHAR2(20 BYTE), 
	"VEHICLE" VARCHAR2(20 BYTE), 
	"DATEINSC" DATE DEFAULT sysdate, 
	"MISSION" NUMBER
   ) SEGMENT CREATION IMMEDIATE 
  PCTFREE 10 PCTUSED 40 INITRANS 1 MAXTRANS 255 NOCOMPRESS LOGGING
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1 BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "SYSTEM" ;
REM INSERTING into SYSTEM.BENEVOLE
SET DEFINE OFF;
Insert into SYSTEM.BENEVOLE (ID,NOM,MAIL,DATENAISS,NUMTEL,ADRESSE,DISPO,VEHICLE,DATEINSC,MISSION) values (13,'mohamed ali','@esprit.tn',to_date('01-JAN-00','DD-MON-RR'),9920,'ariana','actif','mazda',to_date('31-MAR-23','DD-MON-RR'),8);
Insert into SYSTEM.BENEVOLE (ID,NOM,MAIL,DATENAISS,NUMTEL,ADRESSE,DISPO,VEHICLE,DATEINSC,MISSION) values (646,'yosser','@esprti',to_date('28-APR-23','DD-MON-RR'),2316465,'kairouan','active','mercedes',to_date('28-APR-23','DD-MON-RR'),4);
Insert into SYSTEM.BENEVOLE (ID,NOM,MAIL,DATENAISS,NUMTEL,ADRESSE,DISPO,VEHICLE,DATEINSC,MISSION) values (12,'rayene','@esprit.tn',to_date('11-AUG-02','DD-MON-RR'),9920,'arianahhh','afk','audi',to_date('30-MAR-23','DD-MON-RR'),0);
Insert into SYSTEM.BENEVOLE (ID,NOM,MAIL,DATENAISS,NUMTEL,ADRESSE,DISPO,VEHICLE,DATEINSC,MISSION) values (16,'seif','@esprit.tn',to_date('01-JAN-00','DD-MON-RR'),9984475,'mahdia','actif','4x4',to_date('31-MAR-23','DD-MON-RR'),6);
Insert into SYSTEM.BENEVOLE (ID,NOM,MAIL,DATENAISS,NUMTEL,ADRESSE,DISPO,VEHICLE,DATEINSC,MISSION) values (18,'omar','@esprit.tn',to_date('01-JAN-00','DD-MON-RR'),97846,'mahdia','afk','quatrelle',to_date('31-MAR-23','DD-MON-RR'),6);
Insert into SYSTEM.BENEVOLE (ID,NOM,MAIL,DATENAISS,NUMTEL,ADRESSE,DISPO,VEHICLE,DATEINSC,MISSION) values (20,'adem','@esprit.tn',to_date('01-JAN-00','DD-MON-RR'),96646,'Gafsa','afk','skoda',to_date('31-MAR-23','DD-MON-RR'),7);
Insert into SYSTEM.BENEVOLE (ID,NOM,MAIL,DATENAISS,NUMTEL,ADRESSE,DISPO,VEHICLE,DATEINSC,MISSION) values (21,'hend','@esprit.tn',to_date('01-JAN-00','DD-MON-RR'),9467675,'ghazela','active','camaro',to_date('31-MAR-23','DD-MON-RR'),3);
Insert into SYSTEM.BENEVOLE (ID,NOM,MAIL,DATENAISS,NUMTEL,ADRESSE,DISPO,VEHICLE,DATEINSC,MISSION) values (22,'nour','@esprit.tn',to_date('01-JAN-00','DD-MON-RR'),9467675,'ghazela','active','mustang',to_date('31-MAR-23','DD-MON-RR'),2);
Insert into SYSTEM.BENEVOLE (ID,NOM,MAIL,DATENAISS,NUMTEL,ADRESSE,DISPO,VEHICLE,DATEINSC,MISSION) values (23,'whatever','@esprit.tn',to_date('01-APR-23','DD-MON-RR'),44568745,null,null,null,to_date('01-APR-23','DD-MON-RR'),0);
Insert into SYSTEM.BENEVOLE (ID,NOM,MAIL,DATENAISS,NUMTEL,ADRESSE,DISPO,VEHICLE,DATEINSC,MISSION) values (4,'jhin','rouri@esprit.tn',to_date('01-JAN-00','DD-MON-RR'),992065,'ariana','actif','porche',to_date('11-APR-23','DD-MON-RR'),0);
--------------------------------------------------------
--  Constraints for Table BENEVOLE
--------------------------------------------------------

  ALTER TABLE "SYSTEM"."BENEVOLE" MODIFY ("NOM" NOT NULL ENABLE);
  ALTER TABLE "SYSTEM"."BENEVOLE" MODIFY ("ID" NOT NULL ENABLE);
