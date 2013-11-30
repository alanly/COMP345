#include "Character.h"
#include <sstream>
#include <ctime>
#include <string>
#include <string.h>
#include <iostream>

using namespace std;

Character::Character(string name, int level) : Entity(name,level)
{
	this->classification = enumUtility::Tank;
}
Character::Character(string name, int level, enumUtility::characterClassifiction classification) : Entity(name,level)
{
	this->classification = classification;
}

Character::~Character(void)
{
}
void Character::levelUp()
{
	this->level++;
	currentExp -= expAtLevel; 
	expAtLevel = levelExpModifier * this->level;
	maxHitPoints += getConstitution() + Dice::roleTenSideDice();
	this->attackBonus++;
	this->numberOfAttacks = (this->level / 5) + 1;
}
void Character::gainExperiance(int exp)
{
	currentExp += exp;
	while(currentExp >= expAtLevel)
	{
		levelUp();
	}
}
int Character::getArmorClass(){
	int total = getDexterity() + 10;
	if(getArmor() != nullptr){
		total += getArmor()->getEnhancement(ItemEnhancement::ARMOUR_CLASS);
	}
	if(getShield() != nullptr){
		total += getShield()->getEnhancement(ItemEnhancement::ARMOUR_CLASS);
	}
	return total;
}

enumUtility::characterClassifiction Character::getClassification()
{
	return this->classification;
}

HelmetItem* Character::getHelmet()
{
	return helmet;
}
ArmourItem* Character::getArmor()
{
	return armor;
}
WeaponItem* Character::getWeapon()
{
	return weapon;
}
ShieldItem* Character::getShield()
{
	return shield;
}
RingItem* Character::getRing1()
{
	return ring1;
}

RingItem* Character::getRing2()
{
	return ring2;
}
BeltItem* Character::getBelt()
{
	return belt;
}

BootsItem* Character::getBoots()
{
	return boots;
}
void Character::setHelmet(HelmetItem* helmet)
{
	this->helmet = helmet;
}
void Character::setArmor(ArmourItem* armor)
{
	this->armor = armor;
}
void Character::setWeapon(WeaponItem* weapon)
{
	this->weapon = weapon;
}
void Character::setShield(ShieldItem* shield)
{
	this->shield = shield;
}
void Character::setRing1(RingItem* ring)
{
	this->ring1 = ring;
}
void Character::setRing2(RingItem* ring)
{
	this->ring2 = ring;
}
void Character::setBelt(BeltItem* belt)
{
	this->belt = belt;
}
void Character::setBoots(BootsItem* boots)
{
	this->boots = boots;
}

void Character::setClassification(enumUtility::characterClassifiction classification)
{
	this->classification = classification;
}

void Character::saveToFile()
{
        string charName = this->getName();
        HelmetItem *helmet = this->helmet;
        ArmourItem *armor = this->armor;
        ShieldItem *shield = this->shield;
        WeaponItem *weapon = this->weapon;
        RingItem *ring1 = this->ring1;
        RingItem *ring2 = this->ring2;
        BootsItem *boots = this->boots;
        BeltItem *belt = this->belt;

        string strength = to_string(this->getStrength());
        string dexterity = to_string(this->getDexterity());
        string charisma = to_string(this->getCharisma());
        string intelligence = to_string(this->getInteligence());
        string constitution = to_string(this->getConstitution());
        string wisdom = to_string(this->getWisdom());
        string armorClass = to_string(this->getArmorClass());
        string damageBonus = to_string(this->getDamageBonus());
        string attackBonus = to_string(this->getAttackBonus());

        XMLDocument doc;
        XMLNode *characterNode = doc.NewElement("Character");

        XMLNode *nameNode = doc.NewElement("Name");
        const char* c = charName.c_str();
        XMLText *nameText = doc.NewText(c);
        nameNode->InsertEndChild(nameText);

        XMLNode *characterClassNode = doc.NewElement("CharacterClass");
        int classification = static_cast<int>(this->classification);
        string convert = to_string(classification);
        c = convert.c_str();
        XMLText *characterClassText = doc.NewText(c);
        characterClassNode->InsertEndChild(characterClassText);

        XMLNode *currentExpNode = doc.NewElement("CurrentExperience");
        convert = to_string(this->currentExp);
        c = convert.c_str();
        XMLText *currentExpText = doc.NewText(c);
        currentExpNode->InsertEndChild(currentExpText);

        XMLNode *expAtLevelNode = doc.NewElement("ExperienceAtLevel");
        convert = to_string(this->expAtLevel);
        c = convert.c_str();
        XMLText *expAtLevelText = doc.NewText(c);
        expAtLevelNode->InsertEndChild(expAtLevelText);

        XMLNode* strengthNode = doc.NewElement("Strength");
        c = strength.c_str();
        XMLText* strengthText = doc.NewText(c);
        strengthNode->InsertEndChild(strengthText);

        XMLNode* dexterityNode = doc.NewElement("Dexterity");
        c = dexterity.c_str();
        XMLText* dexterityText = doc.NewText(c);
        dexterityNode->InsertEndChild(dexterityText);

        XMLNode* charismaNode = doc.NewElement("Charisma");
        c = charisma.c_str();
        XMLText* charismaText = doc.NewText(c);
        charismaNode->InsertEndChild(charismaText);

        XMLNode* intelligenceNode = doc.NewElement("Intelligence");
        c = intelligence.c_str();
        XMLText* intelligenceText = doc.NewText(c);
        intelligenceNode->InsertEndChild(intelligenceText);

        XMLNode* constitutionNode = doc.NewElement("Constitution");
        c = constitution.c_str();
        XMLText* constitutionText = doc.NewText(c);
        constitutionNode->InsertEndChild(constitutionText);

        XMLNode* wisdomNode = doc.NewElement("Wisdom");
        c = wisdom.c_str();
        XMLText* wisdomText = doc.NewText(c);
        wisdomNode->InsertEndChild(wisdomText);

        XMLNode* armorClassNode = doc.NewElement("ArmorClass");
        c = armorClass.c_str();
        XMLText* armorClassText = doc.NewText(c);
        armorClassNode->InsertEndChild(armorClassText);

        XMLNode* damageBonusNode = doc.NewElement("DamageBonus");
        c = damageBonus.c_str();
        XMLText* damageBonusText = doc.NewText(c);
        damageBonusNode->InsertEndChild(damageBonusText);

        XMLNode* attackBonusNode = doc.NewElement("AttackBonus");
        c = attackBonus.c_str();
        XMLText* attackBonusText = doc.NewText(c);
        attackBonusNode->InsertEndChild(attackBonusText);

        //Will refactor this junk if I have time
        string name;
        string description;
        ItemType type;
        Enhancements enhancements;

        XMLNode* helmetNode = doc.NewElement("Helmet");
        XMLNode* ring1Node = doc.NewElement("Ring1");
        XMLNode* ring2Node = doc.NewElement("Ring2");
        XMLNode* weaponNode = doc.NewElement("Weapon");
        XMLNode* shieldNode = doc.NewElement("Shield");
        XMLNode* armourNode = doc.NewElement("Armour");
        XMLNode* beltNode = doc.NewElement("Belt");
        XMLNode* bootsNode = doc.NewElement("Boots");

        //Helmet
        if (this->helmet != NULL)
        {
                XMLNode *nameNode = doc.NewElement("Name");
                name = helmet->getName();
                const char* c = name.c_str();
                XMLText *nameText = doc.NewText(c);
                
                XMLNode *descriptionNode = doc.NewElement("Description");
                description = helmet->getDescription();
                c = description.c_str();
                XMLText *descriptionText = doc.NewText(c);

                XMLNode *typeNode = doc.NewElement("Type");
                type = helmet->getType();
                int t = static_cast<int>(type);
                string convert = to_string(t);
                c = convert.c_str();
                XMLText *typeText = doc.NewText(c);


                XMLNode *enhancementsNode = doc.NewElement("Enhancements");
                XMLNode *enhancementType;
                XMLNode *enhancementValue;
                enhancements = helmet->getEnhancements();
                Enhancements::iterator it;

                for (it = enhancements.begin(); it != enhancements.end(); it++)
                {
                        enhancementType = doc.NewElement("Type");
                        enhancementValue = doc.NewElement("Value");
                        int typeText = static_cast<int>(it->first);
                        int valueText = it->second;

                        convert = to_string(typeText);
                        c = convert.c_str();
                        XMLText *eTypeText = doc.NewText(c);

                        convert = to_string(valueText);
                        c = convert.c_str();
                        XMLText *eValueText = doc.NewText(c);

                        enhancementType->InsertEndChild(eTypeText);
                        enhancementValue->InsertEndChild(eValueText);
                        enhancementsNode->InsertEndChild(enhancementType);
                        enhancementsNode->InsertEndChild(enhancementValue);
                }

                nameNode->InsertEndChild(nameText);
                descriptionNode->InsertEndChild(descriptionText);
                typeNode->InsertEndChild(typeText);
                helmetNode->InsertEndChild(nameNode);
                helmetNode->InsertEndChild(descriptionNode);
                helmetNode->InsertEndChild(typeNode);
                helmetNode->InsertEndChild(enhancementsNode);
        }

        //Ring1
        if (this->ring1 != NULL)
        {
                XMLNode *nameNode = doc.NewElement("Name");
                name = ring1->getName();
                const char* c = name.c_str();
                XMLText *nameText = doc.NewText(c);
                
                XMLNode *descriptionNode = doc.NewElement("Description");
                description = ring1->getDescription();
                c = description.c_str();
                XMLText *descriptionText = doc.NewText(c);

                XMLNode *typeNode = doc.NewElement("Type");
                type = ring1->getType();
                int t = static_cast<int>(type);
                string convert = to_string(t);
                c = convert.c_str();
                XMLText *typeText = doc.NewText(c);

                XMLNode *enhancementsNode = doc.NewElement("Enhancements");
                XMLNode *enhancementType;
                XMLNode *enhancementValue;
                enhancements = ring1->getEnhancements();
                Enhancements::iterator it;

                for (it = enhancements.begin(); it != enhancements.end(); it++)
                {
                        enhancementType = doc.NewElement("Type");
                        enhancementValue = doc.NewElement("Value");
                        int typeText = static_cast<int>(it->first);
                        int valueText = it->second;

                        convert = to_string(typeText);
                        c = convert.c_str();
                        XMLText *eTypeText = doc.NewText(c);

                        convert = to_string(valueText);
                        c = convert.c_str();
                        XMLText *eValueText = doc.NewText(c);

                        enhancementType->InsertEndChild(eTypeText);
                        enhancementValue->InsertEndChild(eValueText);
                        enhancementsNode->InsertEndChild(enhancementType);
                        enhancementsNode->InsertEndChild(enhancementValue);
                }

                nameNode->InsertEndChild(nameText);
                descriptionNode->InsertEndChild(descriptionText);
                typeNode->InsertEndChild(typeText);
                ring1Node->InsertEndChild(nameNode);
                ring1Node->InsertEndChild(descriptionNode);
                ring1Node->InsertEndChild(typeNode);
                ring1Node->InsertEndChild(enhancementsNode);
        }

        //Ring2
        if (this->ring2 != NULL)
        {
                XMLNode *nameNode = doc.NewElement("Name");
                name = ring2->getName();
                const char* c = name.c_str();
                XMLText *nameText = doc.NewText(c);
                
                XMLNode *descriptionNode = doc.NewElement("Description");
                description = ring2->getDescription();
                c = description.c_str();
                XMLText *descriptionText = doc.NewText(c);

                XMLNode *typeNode = doc.NewElement("Type");
                type = ring2->getType();
                int t = static_cast<int>(type);
                string convert = to_string(t);
                c = convert.c_str();
                XMLText *typeText = doc.NewText(c);


                XMLNode *enhancementsNode = doc.NewElement("Enhancements");
                XMLNode *enhancementType;
                XMLNode *enhancementValue;
                enhancements = ring2->getEnhancements();
                Enhancements::iterator it;

                for (it = enhancements.begin(); it != enhancements.end(); it++)
                {
                        enhancementType = doc.NewElement("Type");
                        enhancementValue = doc.NewElement("Value");
                        int typeText = static_cast<int>(it->first);
                        int valueText = it->second;

                        convert = to_string(typeText);
                        c = convert.c_str();
                        XMLText *eTypeText = doc.NewText(c);

                        convert = to_string(valueText);
                        c = convert.c_str();
                        XMLText *eValueText = doc.NewText(c);

                        enhancementType->InsertEndChild(eTypeText);
                        enhancementValue->InsertEndChild(eValueText);
                        enhancementsNode->InsertEndChild(enhancementType);
                        enhancementsNode->InsertEndChild(enhancementValue);
                }

                nameNode->InsertEndChild(nameText);
                descriptionNode->InsertEndChild(descriptionText);
                typeNode->InsertEndChild(typeText);
                ring2Node->InsertEndChild(nameNode);
                ring2Node->InsertEndChild(descriptionNode);
                ring2Node->InsertEndChild(typeNode);
                ring2Node->InsertEndChild(enhancementsNode);
        }

        //Weapon
        if (this->weapon != NULL)
        {
                XMLNode *nameNode = doc.NewElement("Name");
                name = weapon->getName();
                const char* c = name.c_str();
                XMLText *nameText = doc.NewText(c);
                
                XMLNode *descriptionNode = doc.NewElement("Description");
                description = weapon->getDescription();
                c = description.c_str();
                XMLText *descriptionText = doc.NewText(c);

                XMLNode *typeNode = doc.NewElement("Type");
                type = weapon->getType();
                int t = static_cast<int>(type);
                string convert = to_string(t);
                c = convert.c_str();
                XMLText *typeText = doc.NewText(c);


                XMLNode *enhancementsNode = doc.NewElement("Enhancements");
                XMLNode *enhancementType;
                XMLNode *enhancementValue;
                enhancements = weapon->getEnhancements();
                Enhancements::iterator it;

                for (it = enhancements.begin(); it != enhancements.end(); it++)
                {
                        enhancementType = doc.NewElement("Type");
                        enhancementValue = doc.NewElement("Value");
                        int typeText = static_cast<int>(it->first);
                        int valueText = it->second;

                        convert = to_string(typeText);
                        c = convert.c_str();
                        XMLText *eTypeText = doc.NewText(c);

                        convert = to_string(valueText);
                        c = convert.c_str();
                        XMLText *eValueText = doc.NewText(c);

                        enhancementType->InsertEndChild(eTypeText);
                        enhancementValue->InsertEndChild(eValueText);
                        enhancementsNode->InsertEndChild(enhancementType);
                        enhancementsNode->InsertEndChild(enhancementValue);
                }

                nameNode->InsertEndChild(nameText);
                descriptionNode->InsertEndChild(descriptionText);
                typeNode->InsertEndChild(typeText);
                weaponNode->InsertEndChild(nameNode);
                weaponNode->InsertEndChild(descriptionNode);
                weaponNode->InsertEndChild(typeNode);
                weaponNode->InsertEndChild(enhancementsNode);
        }

        //Shield
        if (this->shield != NULL)
        {
                XMLNode *nameNode = doc.NewElement("Name");
                name = shield->getName();
                const char* c = name.c_str();
                XMLText *nameText = doc.NewText(c);
                
                XMLNode *descriptionNode = doc.NewElement("Description");
                description = shield->getDescription();
                c = description.c_str();
                XMLText *descriptionText = doc.NewText(c);

                XMLNode *typeNode = doc.NewElement("Type");
                type = shield->getType();
                int t = static_cast<int>(type);
                string convert = to_string(t);
                c = convert.c_str();
                XMLText *typeText = doc.NewText(c);


                XMLNode *enhancementsNode = doc.NewElement("Enhancements");
                XMLNode *enhancementType;
                XMLNode *enhancementValue;
                enhancements = shield->getEnhancements();
                Enhancements::iterator it;

                for (it = enhancements.begin(); it != enhancements.end(); it++)
                {
                        enhancementType = doc.NewElement("Type");
                        enhancementValue = doc.NewElement("Value");
                        int typeText = static_cast<int>(it->first);
                        int valueText = it->second;

                        convert = to_string(typeText);
                        c = convert.c_str();
                        XMLText *eTypeText = doc.NewText(c);

                        convert = to_string(valueText);
                        c = convert.c_str();
                        XMLText *eValueText = doc.NewText(c);

                        enhancementType->InsertEndChild(eTypeText);
                        enhancementValue->InsertEndChild(eValueText);
                        enhancementsNode->InsertEndChild(enhancementType);
                        enhancementsNode->InsertEndChild(enhancementValue);
                }

                nameNode->InsertEndChild(nameText);
                descriptionNode->InsertEndChild(descriptionText);
                typeNode->InsertEndChild(typeText);
                shieldNode->InsertEndChild(nameNode);
                shieldNode->InsertEndChild(descriptionNode);
                shieldNode->InsertEndChild(typeNode);
                shieldNode->InsertEndChild(enhancementsNode);
        }

        //Armour
        if (this->armor != NULL)
        {
                XMLNode *nameNode = doc.NewElement("Name");
                name = armor->getName();
                const char* c = name.c_str();
                XMLText *nameText = doc.NewText(c);
                
                XMLNode *descriptionNode = doc.NewElement("Description");
                description = armor->getDescription();
                c = description.c_str();
                XMLText *descriptionText = doc.NewText(c);

                XMLNode *typeNode = doc.NewElement("Type");
                type = armor->getType();
                int t = static_cast<int>(type);
                string convert = to_string(t);
                c = convert.c_str();
                XMLText *typeText = doc.NewText(c);


                XMLNode *enhancementsNode = doc.NewElement("Enhancements");
                XMLNode *enhancementType;
                XMLNode *enhancementValue;
                enhancements = armor->getEnhancements();
                Enhancements::iterator it;

                for (it = enhancements.begin(); it != enhancements.end(); it++)
                {
                        enhancementType = doc.NewElement("Type");
                        enhancementValue = doc.NewElement("Value");
                        int typeText = static_cast<int>(it->first);
                        int valueText = it->second;

                        convert = to_string(typeText);
                        c = convert.c_str();
                        XMLText *eTypeText = doc.NewText(c);

                        convert = to_string(valueText);
                        c = convert.c_str();
                        XMLText *eValueText = doc.NewText(c);

                        enhancementType->InsertEndChild(eTypeText);
                        enhancementValue->InsertEndChild(eValueText);
                        enhancementsNode->InsertEndChild(enhancementType);
                        enhancementsNode->InsertEndChild(enhancementValue);
                }

                nameNode->InsertEndChild(nameText);
                descriptionNode->InsertEndChild(descriptionText);
                typeNode->InsertEndChild(typeText);
                armourNode->InsertEndChild(nameNode);
                armourNode->InsertEndChild(descriptionNode);
                armourNode->InsertEndChild(typeNode);
                armourNode->InsertEndChild(enhancementsNode);
        }

        //Belt
        if (this->belt != NULL)
        {
                XMLNode *nameNode = doc.NewElement("Name");
                name = belt->getName();
                const char* c = name.c_str();
                XMLText *nameText = doc.NewText(c);
                
                XMLNode *descriptionNode = doc.NewElement("Description");
                description = belt->getDescription();
                c = description.c_str();
                XMLText *descriptionText = doc.NewText(c);

                XMLNode *typeNode = doc.NewElement("Type");
                type = belt->getType();
                int t = static_cast<int>(type);
                string convert = to_string(t);
                c = convert.c_str();
                XMLText *typeText = doc.NewText(c);


                XMLNode *enhancementsNode = doc.NewElement("Enhancements");
                XMLNode *enhancementType;
                XMLNode *enhancementValue;
                enhancements = belt->getEnhancements();
                Enhancements::iterator it;

                for (it = enhancements.begin(); it != enhancements.end(); it++)
                {
                        enhancementType = doc.NewElement("Type");
                        enhancementValue = doc.NewElement("Value");
                        int typeText = static_cast<int>(it->first);
                        int valueText = it->second;

                        convert = to_string(typeText);
                        c = convert.c_str();
                        XMLText *eTypeText = doc.NewText(c);

                        convert = to_string(valueText);
                        c = convert.c_str();
                        XMLText *eValueText = doc.NewText(c);

                        enhancementType->InsertEndChild(eTypeText);
                        enhancementValue->InsertEndChild(eValueText);
                        enhancementsNode->InsertEndChild(enhancementType);
                        enhancementsNode->InsertEndChild(enhancementValue);
                }

                nameNode->InsertEndChild(nameText);
                descriptionNode->InsertEndChild(descriptionText);
                typeNode->InsertEndChild(typeText);
                beltNode->InsertEndChild(nameNode);
                beltNode->InsertEndChild(descriptionNode);
                beltNode->InsertEndChild(typeNode);
                beltNode->InsertEndChild(enhancementsNode);
        }

        //Boots
        if (this->boots != NULL)
        {
                XMLNode *nameNode = doc.NewElement("Name");
                name = boots->getName();
                const char* c = name.c_str();
                XMLText *nameText = doc.NewText(c);
                
                XMLNode *descriptionNode = doc.NewElement("Description");
                description = boots->getDescription();
                c = description.c_str();
                XMLText *descriptionText = doc.NewText(c);

                XMLNode *typeNode = doc.NewElement("Type");
                type = boots->getType();
                int t = static_cast<int>(type);
                string convert = to_string(t);
                c = convert.c_str();
                XMLText *typeText = doc.NewText(c);

                XMLNode *enhancementsNode = doc.NewElement("Enhancements");
                XMLNode *enhancementType;
                XMLNode *enhancementValue;
                enhancements = boots->getEnhancements();
                Enhancements::iterator it;

                for (it = enhancements.begin(); it != enhancements.end(); it++)
                {
                        enhancementType = doc.NewElement("Type");
                        enhancementValue = doc.NewElement("Value");
                        int typeText = static_cast<int>(it->first);
                        int valueText = it->second;

                        convert = to_string(typeText);
                        c = convert.c_str();
                        XMLText *eTypeText = doc.NewText(c);

                        convert = to_string(valueText);
                        c = convert.c_str();
                        XMLText *eValueText = doc.NewText(c);

                        enhancementType->InsertEndChild(eTypeText);
                        enhancementValue->InsertEndChild(eValueText);
                        enhancementsNode->InsertEndChild(enhancementType);
                        enhancementsNode->InsertEndChild(enhancementValue);
                }

                nameNode->InsertEndChild(nameText);
                descriptionNode->InsertEndChild(descriptionText);
                typeNode->InsertEndChild(typeText);
                bootsNode->InsertEndChild(nameNode);
                bootsNode->InsertEndChild(descriptionNode);
                bootsNode->InsertEndChild(typeNode);
                bootsNode->InsertEndChild(enhancementsNode);
        }

        //helmetNode = (this->convertItemToXML(helmet,helmetNode))->ToNode();
        //cout << helmetNode->ToElement()->Value() << endl;

        characterNode->InsertEndChild(nameNode);
        characterNode->InsertEndChild(characterClassNode);
        characterNode->InsertEndChild(currentExpNode);
        //characterNode->InsertEndChild(expAtLevelNode);
        characterNode->InsertEndChild(strengthNode);
        characterNode->InsertEndChild(dexterityNode);
        characterNode->InsertEndChild(charismaNode);
        characterNode->InsertEndChild(intelligenceNode);
        characterNode->InsertEndChild(constitutionNode);
        characterNode->InsertEndChild(wisdomNode);
        //characterNode->InsertEndChild(armorClassNode);
        //characterNode->InsertEndChild(damageBonusNode);
        //characterNode->InsertEndChild(attackBonusNode);
        characterNode->InsertEndChild(helmetNode);
        characterNode->InsertEndChild(ring1Node);
        characterNode->InsertEndChild(ring2Node);
        characterNode->InsertEndChild(weaponNode);
        characterNode->InsertEndChild(shieldNode);
        characterNode->InsertEndChild(armourNode);
        characterNode->InsertEndChild(beltNode);
        characterNode->InsertEndChild(bootsNode);
        doc.InsertEndChild(characterNode);


        time_t t = time(0);
        struct tm now;
        localtime_s(&now,&t);
        int year = now.tm_year + 1900;
        int month = now.tm_mon + 1;
        int day = now.tm_mday;
        string sYear = to_string(year);
        string sMonth = to_string(month);
        string sDay = to_string(day);
        string date = "sav\\char\\" + this->getName() + "_" + sYear + "_" + sMonth + "_" + sDay + ".xml";
        const char* filename =  date.c_str();
        
        doc.SaveFile(filename);
}
Character* Character::readFromFile(string filename)
{
		filename = "sav\\char\\" + filename;
		const char* f = filename.c_str();
		cout << f << endl;
        XMLDocument doc = new XMLDocument();
        int error = doc.LoadFile(f);
		if(error != 0){
			return nullptr;
		}
        XMLElement* topChildLevel = doc.FirstChildElement("Character")->FirstChildElement("Name");

        //Name
        const char* characterName = topChildLevel->GetText();

        //Character Class
        topChildLevel = topChildLevel->NextSiblingElement();
        enumUtility::characterClassifiction characterClass = static_cast<enumUtility::characterClassifiction>(stoi(topChildLevel->GetText()));

        Character* character = new Character(characterName,0,characterClass);

        //Current experience
        topChildLevel = topChildLevel->NextSiblingElement();
        int currentExperience = stoi(topChildLevel->GetText());
        character->gainExperiance(currentExperience);

        //Strength
        topChildLevel = topChildLevel->NextSiblingElement();
        int strength = stoi(topChildLevel->GetText());
        character->setStrength(strength);

        //Dexterity
        topChildLevel = topChildLevel->NextSiblingElement();
        int dexterity = stoi(topChildLevel->GetText());
        character->setDexterity(dexterity);

        //Charisma
        topChildLevel = topChildLevel->NextSiblingElement();
        int charisma = stoi(topChildLevel->GetText());
        character->setCharisma(charisma);

        //Intelligence
        topChildLevel = topChildLevel->NextSiblingElement();
        int intelligence = stoi(topChildLevel->GetText());
        character->setIntelligence(intelligence);
        
        //Constitution
        topChildLevel = topChildLevel->NextSiblingElement();
        int constitution = stoi(topChildLevel->GetText());
        character->setConstitution(constitution);

        //Wisdom
        topChildLevel = topChildLevel->NextSiblingElement();
        int wisdom = stoi(topChildLevel->GetText());
        character->setWisdom(wisdom);

        string name;
        string description;
        int type;
        Enhancements* enhancements;

        //Helmet
        topChildLevel = topChildLevel->NextSiblingElement();
        if (!topChildLevel->NoChildren())
        {
                HelmetItem* helmet;
                XMLElement* itemAttribute = topChildLevel->FirstChildElement("Name");
                name = itemAttribute->GetText();
                itemAttribute = itemAttribute->NextSiblingElement(); //description
                description = itemAttribute->GetText();
                itemAttribute = itemAttribute->NextSiblingElement(); //type
                type = stoi(itemAttribute->GetText());
                itemAttribute = itemAttribute->NextSiblingElement(); //enhancements
                itemAttribute = itemAttribute->FirstChildElement()->NextSiblingElement(); //intelligence
                int intelligence = stoi(itemAttribute->GetText());
                itemAttribute = itemAttribute->NextSiblingElement()->NextSiblingElement(); //wisdom
                int wisdom = stoi(itemAttribute->GetText());
                itemAttribute = itemAttribute->NextSiblingElement()->NextSiblingElement(); //armor class
                int armorClass = stoi(itemAttribute->GetText());
                helmet = new HelmetItem(name,description,intelligence,wisdom,armorClass);
                character->setHelmet(helmet);
        }

        //Ring 1
        topChildLevel = topChildLevel->NextSiblingElement();
        if (!topChildLevel->NoChildren())
        {
                RingItem* ring1;
                XMLElement* itemAttribute = topChildLevel->FirstChildElement("Name");
                name = itemAttribute->GetText();
                itemAttribute = itemAttribute->NextSiblingElement(); //description
                description = itemAttribute->GetText();
                itemAttribute = itemAttribute->NextSiblingElement(); //type
                type = stoi(itemAttribute->GetText());
                itemAttribute = itemAttribute->NextSiblingElement(); //enhancements
                itemAttribute = itemAttribute->FirstChildElement()->NextSiblingElement(); //armor class
                int armorClass = stoi(itemAttribute->GetText());
                itemAttribute = itemAttribute->NextSiblingElement()->NextSiblingElement(); //strength
                int strength = stoi(itemAttribute->GetText());
                itemAttribute = itemAttribute->NextSiblingElement()->NextSiblingElement(); //constitution
                int constitution = stoi(itemAttribute->GetText());
                itemAttribute = itemAttribute->NextSiblingElement()->NextSiblingElement(); //wisdom
                int wisdom = stoi(itemAttribute->GetText());
                itemAttribute = itemAttribute->NextSiblingElement()->NextSiblingElement(); //charisma
                int charisma = stoi(itemAttribute->GetText());

                ring1 = new RingItem(name,description,armorClass,strength,constitution,wisdom,charisma);
                character->setRing1(ring1);
        }

        //Ring 2
        topChildLevel = topChildLevel->NextSiblingElement();
        if (!topChildLevel->NoChildren())
        {
                RingItem* ring2;
                XMLElement* itemAttribute = topChildLevel->FirstChildElement("Name");
                name = itemAttribute->GetText();
                itemAttribute = itemAttribute->NextSiblingElement(); //description
                description = itemAttribute->GetText();
                itemAttribute = itemAttribute->NextSiblingElement(); //type
                type = stoi(itemAttribute->GetText());
                itemAttribute = itemAttribute->NextSiblingElement(); //enhancements
                itemAttribute = itemAttribute->FirstChildElement()->NextSiblingElement(); //armor class
                int armorClass = stoi(itemAttribute->GetText());
                itemAttribute = itemAttribute->NextSiblingElement()->NextSiblingElement(); //strength
                int strength = stoi(itemAttribute->GetText());
                itemAttribute = itemAttribute->NextSiblingElement()->NextSiblingElement(); //constitution
                int constitution = stoi(itemAttribute->GetText());
                itemAttribute = itemAttribute->NextSiblingElement()->NextSiblingElement(); //wisdom
                int wisdom = stoi(itemAttribute->GetText());
                itemAttribute = itemAttribute->NextSiblingElement()->NextSiblingElement(); //charisma
                int charisma = stoi(itemAttribute->GetText());

                ring2 = new RingItem(name,description,armorClass,strength,constitution,wisdom,charisma);
                character->setRing2(ring2);
        }

        //Weapon
        topChildLevel = topChildLevel->NextSiblingElement();
        if (!topChildLevel->NoChildren())
        {
                WeaponItem* weapon;
                XMLElement* itemAttribute = topChildLevel->FirstChildElement("Name");
                name = itemAttribute->GetText();
                itemAttribute = itemAttribute->NextSiblingElement(); //description
                description = itemAttribute->GetText();
                itemAttribute = itemAttribute->NextSiblingElement(); //type
                type = stoi(itemAttribute->GetText());
                itemAttribute = itemAttribute->NextSiblingElement(); //enhancements
                itemAttribute = itemAttribute->FirstChildElement()->NextSiblingElement(); //attack bonus
                int attackBonus = stoi(itemAttribute->GetText());
                itemAttribute = itemAttribute->NextSiblingElement()->NextSiblingElement(); //damage bonus
                int damageBonus = stoi(itemAttribute->GetText());

                weapon = new WeaponItem(name,description,attackBonus,damageBonus);
                character->setWeapon(weapon);
        }

        //Shield
        topChildLevel = topChildLevel->NextSiblingElement();
        if (!topChildLevel->NoChildren())
        {
                ShieldItem* shield;
                XMLElement* itemAttribute = topChildLevel->FirstChildElement("Name");
                name = itemAttribute->GetText();
                itemAttribute = itemAttribute->NextSiblingElement(); //description
                description = itemAttribute->GetText();
                itemAttribute = itemAttribute->NextSiblingElement(); //type
                type = stoi(itemAttribute->GetText());
                itemAttribute = itemAttribute->NextSiblingElement(); //enhancements
                itemAttribute = itemAttribute->FirstChildElement()->NextSiblingElement(); //armor class
                int armorClass = stoi(itemAttribute->GetText());

                shield = new ShieldItem(name,description,armorClass);
                character->setShield(shield);
        }

        //Armour
        topChildLevel = topChildLevel->NextSiblingElement();
        if (!topChildLevel->NoChildren())
        {
                ArmourItem* armour;
                XMLElement* itemAttribute = topChildLevel->FirstChildElement("Name");
                name = itemAttribute->GetText();
                itemAttribute = itemAttribute->NextSiblingElement(); //description
                description = itemAttribute->GetText();
                itemAttribute = itemAttribute->NextSiblingElement(); //type
                type = stoi(itemAttribute->GetText());
                itemAttribute = itemAttribute->NextSiblingElement(); //enhancements
                itemAttribute = itemAttribute->FirstChildElement()->NextSiblingElement(); //armor class
                int armorClass = stoi(itemAttribute->GetText());

                armour = new ArmourItem(name,description,armorClass);
                character->setArmor(armour);
        }

        //Belt
        topChildLevel = topChildLevel->NextSiblingElement();
        if (!topChildLevel->NoChildren())
        {
                BeltItem* belt;
                XMLElement* itemAttribute = topChildLevel->FirstChildElement("Name");
                name = itemAttribute->GetText();
                itemAttribute = itemAttribute->NextSiblingElement(); //description
                description = itemAttribute->GetText();
                itemAttribute = itemAttribute->NextSiblingElement(); //type
                type = stoi(itemAttribute->GetText());
                itemAttribute = itemAttribute->NextSiblingElement(); //enhancements
                itemAttribute = itemAttribute->NextSiblingElement()->NextSiblingElement(); //constitution
                int constitution = stoi(itemAttribute->GetText());
                itemAttribute = itemAttribute->NextSiblingElement()->NextSiblingElement(); //strength
                int strength = stoi(itemAttribute->GetText());

                belt = new BeltItem(name,description,constitution,strength);
                character->setBelt(belt);
        }

        //Boots
        topChildLevel = topChildLevel->NextSiblingElement();
        if (!topChildLevel->NoChildren())
        {
                BootsItem* boots;
                XMLElement* itemAttribute = topChildLevel->FirstChildElement("Name");
                name = itemAttribute->GetText();
                itemAttribute = itemAttribute->NextSiblingElement(); //description
                description = itemAttribute->GetText();
                itemAttribute = itemAttribute->NextSiblingElement(); //type
                type = stoi(itemAttribute->GetText());
                itemAttribute = itemAttribute->NextSiblingElement(); //enhancements
                itemAttribute = itemAttribute->FirstChildElement()->NextSiblingElement(); //armor class
                int armorClass = stoi(itemAttribute->GetText());
                itemAttribute = itemAttribute->NextSiblingElement()->NextSiblingElement(); //dexterity
                int dexterity = stoi(itemAttribute->GetText());

                boots = new BootsItem(name,description,armorClass,dexterity);
                character->setBoots(boots);
        }

        return character;

}
