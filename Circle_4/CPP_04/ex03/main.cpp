/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 16:49:33 by viny              #+#    #+#             */
/*   Updated: 2025/10/14 18:33:15 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Ice.hpp"
#include "Cure.hpp"
#include "ICharacter.hpp"
#include "AMateria.hpp"
#include "MateriaSource.hpp"
#include "IMateriaSource.hpp"
#include "Character.hpp"

int main(void) {
    std::cout << "=== Subject test ===" << std::endl;
    {
        IMateriaSource* src = new MateriaSource();
        src->learnMateria(new Ice());
        src->learnMateria(new Cure());

        ICharacter* me = new Character("me");
        
        AMateria* tmp;
        tmp = src->createMateria("ice");
        me->equip(tmp);
        tmp = src->createMateria("cure");
        me->equip(tmp);

        ICharacter* bob = new Character("bob");
        
        me->use(0, *bob);
        me->use(1, *bob);

        delete bob;
        delete me;
        delete src;
    }

    std::cout << "\n=== Full inventory test ===" << std::endl;
    {
        ICharacter* hero = new Character("Hero");
        
        hero->equip(new Ice());
        hero->equip(new Cure());
        hero->equip(new Ice());
        hero->equip(new Cure());
        
        hero->equip(new Ice());

        delete hero;
    }

    std::cout << "\n=== Unequip & memory tests ===" << std::endl;
    {
        ICharacter* mage = new Character("Mage");
        AMateria* ice = new Ice();
        AMateria* cure = new Cure();

        mage->equip(ice);
        mage->equip(cure);

        ICharacter* warrior = new Character("warrior");

        mage->use(0, *warrior);
		AMateria* dropped = ice;
        mage->unequip(0);

        mage->use(0, *warrior);
        mage->use(1, *warrior);
        
		delete dropped;
        delete warrior;
        delete mage;
    }

    std::cout << "\n=== Deep copy test ===" << std::endl;
    {
        Character original("Original");
        original.equip(new Ice());
        original.equip(new Cure());
        
        Character copy(original);
        copy = Character("Copy");
        
        ICharacter* ennemy = new Character("ennemy");
        original.use(0, *ennemy);
        copy.use(0, *ennemy);
        
        delete ennemy;
    }

    std::cout << "\n=== MateriaSource test ===" << std::endl;
    {
        IMateriaSource* source = new MateriaSource();
        
        source->learnMateria(new Ice());
        source->learnMateria(new Cure());
        
        AMateria* ice1 = source->createMateria("ice");
        AMateria* cure1 = source->createMateria("cure");
        AMateria* unknown = source->createMateria("fire");
        
        std::cout << "Ice type: " << (ice1 ? ice1->getType() : "NULL") << std::endl;
        std::cout << "Cure type: " << (cure1 ? cure1->getType() : "NULL") << std::endl;
        std::cout << "Unknown type: " << (unknown ? unknown->getType() : "NULL") << std::endl;
        
        delete ice1;
        delete cure1;
        delete source;
    }

    std::cout << "=== End of tests ===" << std::endl;
        
    return 0;
}