/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 22:20:36 by vnieto-j          #+#    #+#             */
/*   Updated: 2025/08/26 21:34:07 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <istream>
#include <sstream>

static bool    replace_all(const std::string &input, const std::string &s1,
            const std::string &s2, std::string &output)
{
    if (s1.empty())
        return (false);
    output.clear();
    std::string::size_type pos = 0;
    while (true)
    {
        std::string::size_type found = input.find(s1, pos);
        if (found == std::string::npos)
        {
            output.append(input, pos, std::string::npos);
            break;
        }
        //Ce qui precede l'occurence
        output.append(input, pos, found - pos);
        //La subtitution
        output.append(s2);
        //On saute l'occurence trouvee
        pos = found + s1.size();
    }
    return (true);
}

static bool    checkArgv(std::string filename, std::string s1)
{
    if (filename.empty())
    {
        std::cout << "filename is empty" << std::endl;
        return (false);
    }
    if (s1.empty())
    {
        std::cout << "s1 is empty" << std::endl;
        return (false);
    }
    return (true);
}

int main(int argc, char **argv)
{
    if (argc != 4)
        return (std::cout << "Usage : \"file\" \"s1\" \"s2\"\n", 1);
    
    std::string filename = argv[1];
    std::string s1 = argv[2];
    std::string s2= argv[3];
    
    if (!checkArgv(filename, s1))
        return (1);
    
    //Lecture du fichier avec mode de preservation des octets
    std::ifstream in(filename.c_str(), std::ios::in | std::ios::binary);
    if (!in)
    {
        std::cout << "Error : cannot open file " << filename << " .\n";
        return (1);
    }
    //Creation d'un lfux de sortie (possede un buffer std::string interne)
    std::ostringstream buffer;
    //in.rdbuf(); renvoie le pointeur vers le buffer std::streambuf* (derriere if stream (file open))
    //pompe tout les octet de in pour les reiriger vers buffer
    buffer << in.rdbuf();
    //On va verifier si l'operation s'est bien passer
    // On va cehcker 
    if (!in.good() && !in.eof())
    {
        std::cout << "Error : read failure.\n";
        return (1);
    }
    const std::string content = buffer.str();

    //remplacement
    
    std::string replaced;
    if (!replace_all(content, s1, s2, replaced))
    {
        std::cout << "Error : replacement failed.\n";
        return (1);
    }

    //Ecriture du fichier de sortie 
    const std::string outname = filename + ".replace";
    std::ofstream out (outname.c_str(), std::ios::out | std::ios::binary | std::ios::trunc);
    
    if (!out)
    {
        std::cout << "Error : cannot open output file'" << outname << "'.\n";
        return (1);
    }
    out.write(replaced.data(), static_cast<std::streamsize>(replaced.size()));
    if (!out.good())
    {
        std::cout << "Error: write failure.\n";
        return (1);
    }
    return (0);
}






/*
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

static bool replace_all(const std::string &input,
                        const std::string &s1,
                        const std::string &s2,
                        std::string &output)
{
    if (s1.empty()) return false; // sinon boucle infinie
    output.clear();

    std::string::size_type pos = 0;
    while (true) {
        std::string::size_type found = input.find(s1, pos);
        if (found == std::string::npos) {
            output.append(input, pos, std::string::npos); // le reste
            break;
        }
        // tout ce qui précède l’occurrence
        output.append(input, pos, found - pos);
        // la substitution
        output.append(s2);
        // on saute l’occurrence trouvée
        pos = found + s1.size();
    }
    return true;
}

int main(int argc, char **argv)
{
    if (argc != 4) {
        std::cerr << "Usage: " << (argc > 0 ? argv[0] : "replace")
                  << " <filename> <s1> <s2>\n";
        return 1;
    }

    const std::string filename = argv[1];
    const std::string s1 = argv[2];
    const std::string s2 = argv[3];

    if (filename.empty()) {
        std::cerr << "Error: empty filename.\n";
        return 1;
    }
    if (s1.empty()) {
        std::cerr << "Error: s1 must not be empty.\n";
        return 1;
    }

    // Lecture du fichier entrée (binaire pour préserver les octets)
    std::ifstream in(filename.c_str(), std::ios::in | std::ios::binary);
    if (!in) {
        std::cerr << "Error: cannot open input file '" << filename << "'.\n";
        return 1;
    }
    std::ostringstream buffer;
    buffer << in.rdbuf();
    if (!in.good() && !in.eof()) {
        std::cerr << "Error: read failure.\n";
        return 1;
    }
    const std::string content = buffer.str();

    // Remplacement
    std::string replaced;
    if (!replace_all(content, s1, s2, replaced)) {
        std::cerr << "Error: replacement failed (s1 empty?).\n";
        return 1;
    }

    // Écriture du fichier sortie
    const std::string outname = filename + ".replace";
    std::ofstream out(outname.c_str(),
                      std::ios::out | std::ios::binary | std::ios::trunc);
    if (!out) {
        std::cerr << "Error: cannot open output file '" << outname << "'.\n";
        return 1;
    }
    out.write(replaced.data(), static_cast<std::streamsize>(replaced.size()));
    if (!out.good()) {
        std::cerr << "Error: write failure.\n";
        return 1;
    }

    return 0;
}
*/