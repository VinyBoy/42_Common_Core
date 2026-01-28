/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 07:21:35 by viny              #+#    #+#             */
/*   Updated: 2025/10/14 18:10:43 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"
#include "Cat.hpp"
#include "Dog.hpp"
#include "Brain.hpp"

int main(void)
{
	// std::cout << "\n\t\t------Animal------\n\n";
	// Animal A ("Dog");
	// A.makeSound();
	// Animal B ("Cat");
	// B.makeSound();
	// Animal C ("SKILIPIPAPA");
	// C.makeSound();

	std::cout << "\n\t\t------Cat------\n\n";
	Animal *D = new Cat;
	D->makeSound();
	delete D;

	std::cout << "\n\t\t------Dog------\n\n";
	Animal *E = new Dog;
	E->makeSound();
	delete E;

	std::cout << "\n\t\t------Brain------\n\n";
	
	Animal* animals[10];
	
	for (int i = 0; i < 10; i++)
	{
		if (i < 5)
			animals[i] = new Dog();
		else
			animals[i] = new Cat();
	}
	for (int i = 0; i < 10; i++)
	{
		animals[i]->makeSound();
	}
	for (int i = 0; i < 10; i++)
		delete animals[i];

	std::cout << "\n\t\t------ Test Dog Brain------\n\n";
	{
		Dog Brain;
		Brain.getBrain()->setIdeas("\nThis is a Dog's brain from the stack", 1);
		std::cout << Brain.getBrain()->getIdeas(0) << std::endl;
		Dog *BrainTwo = new Dog();
		BrainTwo->getBrain()->setIdeas("Where is my master 🐶 ? \n", 1);
		BrainTwo->getBrain()->setIdeas("Where is my master 🐶 ? \n", -6);
		std::cout << "Hello Dog's brain ! Do you have an idea ?\n\n" << BrainTwo->getBrain()->getIdeas(1) << std::endl;
		std::cout << "Hello Dog's brain ! Do you have an idea ?\n\n" << BrainTwo->getBrain()->getIdeas(5) << std::endl;
		delete BrainTwo;
	}
	std::cout << "\n\t\t------ Test Deep Copy------\n\n";
	{
		Dog d1;
		d1.getBrain()->setIdeas("Idea from d1", 1);
		Dog d2 = d1;
		std::cout << d2.getBrain()->getIdeas(0) << std::endl;
	}
	return (0);
}