--------------------------------------------------------
--  Fichier créé - mardi-mars-14-2023   
--------------------------------------------------------
DROP TABLE "SYSTEM"."RECUPERER";
--------------------------------------------------------
--  DDL for Table RECUPERER
--------------------------------------------------------

  CREATE TABLE "SYSTEM"."RECUPERER" 
   (	"ID_DONATEUR" NUMBER, 
	"ID_BENEVOLE" NUMBER
   ) PCTFREE 10 PCTUSED 40 INITRANS 1 MAXTRANS 255 NOCOMPRESS LOGGING
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1 BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "SYSTEM" ;
REM INSERTING into SYSTEM.RECUPERER
SET DEFINE OFF;
--------------------------------------------------------
--  Constraints for Table RECUPERER
--------------------------------------------------------

  ALTER TABLE "SYSTEM"."RECUPERER" MODIFY ("ID_BENEVOLE" NOT NULL ENABLE);
  ALTER TABLE "SYSTEM"."RECUPERER" MODIFY ("ID_DONATEUR" NOT NULL ENABLE);
