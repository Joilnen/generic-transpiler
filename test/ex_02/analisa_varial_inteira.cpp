/**
 * Aluno: joilnen leite
 */
#include <boost/spirit/include/qi.hpp>
#include <boost/variant.hpp>
#include <string>
#include <vector>
#include <iostream>

using namespace boost::spirit;

template <typename Iterator, typename Skipper>
struct pytoc_grammar : qi::grammar<Iterator,
  std::vector<std::string>(), Skipper> {
    pytoc_grammar() : pytoc_grammar::base_type{codigo} {
        variavel_inteira = ascii::char_ > *ascii::alnum >> lit('=') >> qi::int_ >> lit(';');
        codigo = *variavel_inteira;
    }
    qi::rule<Iterator, std::string(), Skipper> variavel_inteira;
    qi::rule<Iterator, boost::variant<int, bool>(), Skipper> value;
    qi::rule<Iterator, std::vector<std::string>(), Skipper>
        codigo;
};

int main()
{
    std::string s;
    std::getline(std::cin, s);
    auto it = s.begin();
    pytoc_grammar<std::string::iterator, ascii::space_type> g;
    std::vector<std::string> v;
    if (qi::phrase_parse(it, s.end(), g, ascii::space, v)) {
        for (const auto& elem : v)
            std::cout << elem << "\n";
    }
    if (it != std::end(s))
        std::cerr << "Erro em " << *it << "\n";
}

