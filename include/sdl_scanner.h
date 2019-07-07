#ifndef SDL_SCANNER_H
#define SDL_SCANNER_H

#if !defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

#include <parser.auto.h>
#include <sdl_token_info.h>
#include <sdl_token_info.h>

namespace piranha {

	class SdlScanner : public yyFlexLexer {
	public:
		SdlScanner(std::istream *in) : yyFlexLexer(in) {
			m_loc = new piranha::SdlParser::location_type();
			m_loc->colStart = m_loc->colEnd = 1;
			m_loc->lineStart = m_loc->lineEnd = 1;
		}

		using FlexLexer::yylex;

		virtual int yylex(piranha::SdlParser::semantic_type *lval,
			piranha::SdlParser::location_type *location);

	private:
		void comment();
		void count();
		void countChar(char c);
		void step();

		template <typename T>
		void buildValue(const T &data, piranha::SdlParser::location_type *location, bool valid=true) {
			typedef T_SdlTokenInfo<T> _TokenInfo;

			_TokenInfo info(data, m_loc->lineStart, m_loc->lineEnd, 
				m_loc->colStart, m_loc->colEnd);
			info.valid = valid;
			m_yylval->build<_TokenInfo>(info);
			*location = info;
		}

		piranha::SdlParser::semantic_type *m_yylval = nullptr;
		piranha::SdlParser::location_type *m_loc = nullptr;
	};

} /* namespace piranha */

#endif /* SDL_SCANNER_H */
