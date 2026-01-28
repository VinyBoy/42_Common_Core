/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 07:21:35 by viny              #+#    #+#             */
/*   Updated: 2025/10/14 17:44:32 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"
#include "Cat.hpp"
#include "Dog.hpp"

int main(void)
{
	std::cout << "\n\t\t------Animal------\n\n";
	Animal A ("Dog");
	A.makeSound();
	Animal B ("Cat");
	B.makeSound();
	Animal C ("SKILIPIPAPA");
	C.makeSound();

	std::cout << "\n\t\t------Cat------\n\n";
	Animal *D = new Cat;
	D->makeSound();
	delete D;

	std::cout << "\n\t\t------Dog------\n\n";
	Animal *E = new Dog;
	E->makeSound();
	delete E;

	std::cout << "\n\t\t------WrongAnimal------\n\n";
	WrongAnimal *caspar = new WrongCat;
	caspar->makeSound();
	delete caspar;

	return (0);
}

// int main()
// {
// const Animal* meta = new Animal();
// const Animal* j = new Dog();
// const Animal* i = new Cat();
// std::cout << j->getType() << " " << std::endl;
// std::cout << i->getType() << " " << std::endl;
// i->makeSound(); //will output the cat sound!
// j->makeSound();
// meta->makeSound();
// return 0;
// }