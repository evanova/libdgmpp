--Missing groupID fix
UPDATE dgmExpressions SET expressionGroupID=74 WHERE expressionID=663;
UPDATE dgmExpressions SET expressionGroupID=55 WHERE expressionID=649;
UPDATE dgmExpressions SET expressionGroupID=53 WHERE expressionID=658;
UPDATE dgmExpressions SET expressionGroupID=54 WHERE expressionID=641;
UPDATE dgmExpressions SET expressionGroupID=54 WHERE expressionID=641;

--Missing typeID fix
UPDATE dgmExpressions SET expressionTypeID=3422 WHERE expressionID=1728;
UPDATE dgmExpressions SET expressionTypeID=3423 WHERE expressionID=1555;
UPDATE dgmExpressions SET expressionTypeID=3452 WHERE expressionID=1506;

--Filter invTypes
delete from invCategories where categoryID not in (1, 2, 4, 8, 17, 18, 20, 7, 6, 16, 23, 32, 41, 42, 43, 65, 66, 87);
delete from invGroups where categoryID not in (select categoryID from invCategories);
delete from invGroups where categoryID = 2 AND groupName <> "Effect Beacon";
delete from invTypes where groupID not in (select groupID from invGroups);
delete from dgmTypeAttributes where typeID not in (select typeID from invTypes);
delete from dgmTypeEffects where typeID not in (select typeID from invTypes);
delete from dgmEffects where effectID not in (select effectID from dgmTypeEffects);

--Missing chargeSize
INSERT INTO dgmTypeAttributes (typeID,attributeID,value) VALUES(263,128,0);
INSERT INTO dgmTypeAttributes (typeID,attributeID,value) VALUES(33330,128,0);

--Subsystems fix
UPDATE dgmTypeAttributes SET value=4 WHERE attributeID=1367;

--Online effect fix
UPDATE dgmEffects SET effectCategory = 4 WHERE effectName IN ("online", "onlineForStructures")
