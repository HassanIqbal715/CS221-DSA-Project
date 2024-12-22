#pragma once
#include <typeinfo>
#include "Skill.hpp"
#include "unordered_map"
#include "queue"
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <string>
using namespace std;

enum SkillType{ATTACK, BUFF};

class SkillTree{
private:
    struct SkillNode {
        SkillNode* left;
        SkillNode* right;
        SkillNode* parent;
        Skill* skill;
        SkillType skillType;
        bool unlocked;

        SkillNode(Skill* s, SkillType type) :
            left(nullptr), right(nullptr), parent(nullptr),
            skill(s), skillType(type), unlocked(false) {}
    };

private:
    static SkillTree* sInstance;

    SkillNode* root;

    SkillNode* createSkillNode(Skill* skill, SkillType type, SkillNode* parent = nullptr) {
        SkillNode* node = new SkillNode(skill, type);
        node->parent = parent;

        // Add node to the map
        skillMap[skill->ID] = node;

        if (parent) {
            if (!parent->left) {
                parent->left = node;
            } else if (!parent->right) {
                parent->right = node;
            } else {
                cerr << "Parent ID " << parent->skill->ID << " already has two children.\n";
            }
        }
        return node;
    }

    SkillTree() : root(nullptr) {
        
        root = createSkillNode(new AttackSkill(1, "Slash", "A quick precise attack with a sword.", 250), ATTACK);

        SkillNode* node2 = createSkillNode(new AttackSkill(2, "Heavy Strike", "A powerful overhead swing with a weapon.", 500), ATTACK, root);
        SkillNode* node3 = createSkillNode(new AttackSkill(3, "Flaming Arrow", "An arrow engulfed in flames dealing fire damage.", 750), ATTACK, root);

        SkillNode* node4 = createSkillNode(new AttackSkill(4, "Whirlwind", "Spin with a weapon hitting all nearby enemies.", 800), ATTACK, node2);
        SkillNode* node5 = createSkillNode(new AttackSkill(5, "Shield Bash", "A strike with your shield that stuns the target.", 1000), ATTACK, node2);

        SkillNode* node6 = createSkillNode(new AttackSkill(6, "Poison Dagger", "A quick stab that applies poison damage.", 600), ATTACK, node3);
        SkillNode* node7 = createSkillNode(new AttackSkill(7, "Piercing Shot", "A powerful arrow that pierces through multiple enemies.", 1200), ATTACK, node3);

        SkillNode* node8 = createSkillNode(new AttackSkill(8, "Frost Spike", "Summon an icy spike to strike and slow the enemy.", 1500), ATTACK, node4);
        SkillNode* node9 = createSkillNode(new AttackSkill(9, "Ground Smash", "Strike the ground to deal damage and stagger enemies.", 1700), ATTACK, node4);

        SkillNode* node10 = createSkillNode(new AttackSkill(10, "Shadow Strike", "A stealth attack that deals high critical damage.", 2500), ATTACK, node5);

        createSkillNode(new BuffSkill(11, "Strength Aura", "Boosts the strength", 1.2, BuffSkill::Buff::ATTACK), BUFF, node5);
        createSkillNode(new BuffSkill(12, "Healing Light", "Restores health", 1.5, BuffSkill::Buff::HEALTH), BUFF, node6);

        createSkillNode(new BuffSkill(13, "Iron Skin", "Temporarily increases your armor's defense.", 1.2, BuffSkill::Buff::DEFENSE), BUFF, node6);
        createSkillNode(new BuffSkill(14, "Haste", "Increases movement and attack speed.", 1.2, BuffSkill::Buff::SPEED), BUFF, node7);

        createSkillNode(new BuffSkill(15, "Mana Flow", "Regenerates mana faster over a short duration.", 1.2, BuffSkill::Buff::HEALTH), BUFF, node7);
        createSkillNode(new BuffSkill(16, "Battle Cry", "Increases the morale and attack power of nearby allies.", 1.5, BuffSkill::Buff::ATTACK), BUFF, node8);

        createSkillNode(new BuffSkill(17, "Shield Wall", "Creates a protective barrier that reduces incoming damage.", 1.8, BuffSkill::Buff::DEFENSE), BUFF, node8);
        createSkillNode(new BuffSkill(18, "Eagle Eye", "Increases your accuracy and critical hit chance.", 2, BuffSkill::Buff::ATTACK), BUFF, node9);

        createSkillNode(new BuffSkill(19, "Regeneration", "Gradually restores health over a longer period.", 2, BuffSkill::Buff::HEALTH), BUFF, node9);
        createSkillNode(new BuffSkill(20, "Ward of Light", "Provides resistance to dark magic for a short time.", 2, BuffSkill::Buff::DEFENSE), BUFF, node10);
    }

public:
    unordered_map<int, SkillNode*> skillMap;    
//     SkillTree() : root(nullptr) {
//     ifstream file("database/skills.txt");

//     if (!file.is_open()) {
//         cerr << "Error opening file.\n";
//         return;
//     }

//     string readLine;
//     while (getline(file, readLine)) {
//         if (readLine.empty()) {
//             cerr << "Skipping empty line.\n";
//             continue;
//         }

//         stringstream ss(readLine);
//         int id, skillFactor, parentID = -1;
//         string name, description, type, buffType, line;

//         try {
//             getline(ss, line, ',');
//             if (line.empty()) throw invalid_argument("ID field is empty.");
//             id = stoi(line);

//             getline(ss, name, ',');
//             if (name.empty()) throw invalid_argument("Name field is empty.");

//             getline(ss, description, ',');
//             if (description.empty()) throw invalid_argument("Description field is empty.");

//             getline(ss, line, ',');
//             if (line.empty()) throw invalid_argument("Skill factor field is empty.");
//             skillFactor = stoi(line);

//             getline(ss, type, ',');
//             if (type.empty()) throw invalid_argument("Type field is empty.");

//             if (type == "BUFF") {
//                 getline(ss, buffType, ',');
//                 if (buffType.empty()) throw invalid_argument("Buff type field is empty.");
//             }

//             if (getline(ss, line, ',')) {
//                 if (line == "null") {
//                     parentID = -1;
//                 } else {
//                     parentID = stoi(line);
//                 }
//             }
//         } catch (const exception& e) {
//             cerr << "Error parsing line: " << readLine << " - " << e.what() << endl;
//             continue; // Skip this line
//         }

//         Skill* skill = nullptr;
//         SkillType skillType = (type == "ATTACK") ? ATTACK : BUFF;

//         try {
//             if (type == "ATTACK") {
//                 skill = new AttackSkill(id, name, description, skillFactor);
//             } else if (type == "BUFF") {
//                 BuffSkill::Buff buff;
//                 if (buffType == "ATTACK") buff = BuffSkill::Buff::ATTACK;
//                 else if (buffType == "HEALTH") buff = BuffSkill::Buff::HEALTH;
//                 else if (buffType == "DEFENSE") buff = BuffSkill::Buff::DEFENSE;
//                 else if (buffType == "SPEED") buff = BuffSkill::Buff::SPEED;
//                 else throw invalid_argument("Invalid Buff type: " + buffType);

//                 skill = new BuffSkill(id, name, description, skillFactor, buff);
//             }
//         } catch (const exception& e) {
//             cerr << "Error creating skill for ID " << id << ": " << e.what() << endl;
//             continue; // Skip this skill
//         }

//         if (!skill) {
//             cerr << "Failed to create skill for ID " << id << endl;
//             continue;
//         }

//         SkillNode* node = new SkillNode(skill, skillType);
//         skillMap[id] = node;

//         if (parentID == -1) {
//             if (root) {
//                 cerr << "Multiple roots detected. Skipping ID " << id << endl;
//                 delete node;
//                 continue;
//             }
//             root = node;
//         } else {
//             if (skillMap.find(parentID) == skillMap.end()) {
//                 cerr << "Parent ID " << parentID << " not found for child ID " << id << endl;
//                 delete node;
//                 continue;
//             }

//             SkillNode* parent = skillMap[parentID];
//             if (!parent->left) {
//                 parent->left = node;
//             } else if (!parent->right) {
//                 parent->right = node;
//             } else {
//                 cerr << "Parent ID " << parentID << " has more than two children. Skipping ID " << id << endl;
//                 delete node;
//                 continue;
//             }
//             node->parent = parent;
//         }
//     }

//     file.close();
// }
    static SkillTree* Instance() {
        if (sInstance == nullptr)
            sInstance = new SkillTree();
        return sInstance;
    }

    void levelOrderTraversal() {

        if (!root) {
            cout << "The tree is empty.\n";
            return;
        }

        queue<SkillNode*> q; 
        q.push(root);

        while (!q.empty()) {
            SkillNode* current = q.front();
            q.pop();
            
            cout << "Skill ID: " << current->skill->ID
                 << ", Name: " << current->skill->name
                 << ", Description: " << current->skill->description
                 << ", Type: " << (current->skillType == ATTACK ? "Attack" : "Buff")
                 << ", Unlocked: " << (current->unlocked ? "Yes" : "No") << std::endl;

            if (current->left) {
                q.push(current->left);
            }
            if (current->right) {
                q.push(current->right);
            }
        }
    }

    void printUnlocked() {
        if (!root) {
            cout << "The tree is empty.\n";
            return;
        }

        queue<SkillNode*> q; 
        q.push(root);

        while (!q.empty()) {
            SkillNode* current = q.front();
            q.pop();
            
            if (current->unlocked == true) {
                cout << "Skill ID: " << current->skill->ID
                    << ", Name: " << current->skill->name
                    << ", Description: " << current->skill->description
                    << ", Type: " << (current->skillType == ATTACK ? "Attack" : "Buff")
                    << ", Unlocked: " << (current->unlocked ? "Yes" : "No") << std::endl;

                if (current->left) {
                    q.push(current->left);
                }
                if (current->right) {
                    q.push(current->right);
                }
            }
        }       
    }

    static void release() {
        delete sInstance;
        sInstance = nullptr;
    }

    virtual ~SkillTree() {

    }
};