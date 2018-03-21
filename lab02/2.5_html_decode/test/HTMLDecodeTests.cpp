#include "../html_decode/HTMLDecode.hpp"
#include "catch.hpp"

TEST_CASE("Empty text decodes into empty text", "[decode]")
{
	CHECK(HtmlDecode("") == "");
}

TEST_CASE("Text without html entities does not change", "[decode]")
{
	std::string text("Hello, World!");
	CHECK(HtmlDecode(text) == text);
}

TEST_CASE("All possible html entities are recognized", "[decode]")
{
	CHECK(HtmlDecode(R"(Cat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;s)") == R"(Cat <says> "Meow". M&M's)");
}

TEST_CASE("Unknown entities remain the same", "[decode]")
{
	CHECK(HtmlDecode("&kek;") == "&kek;");
	CHECK(HtmlDecode("&copy;") == "&copy;");
}

TEST_CASE("Only escaped entities are changed", "[decode]")
{
	CHECK(HtmlDecode("amp;&amp") == "amp;&amp");
}

TEST_CASE("Decodes properly when ampersand was met earlier", "[decode]")
{
	CHECK(HtmlDecode("&amp&amp;") == "&amp&");
	CHECK(HtmlDecode("&&amp;") == "&&");
}

TEST_CASE("Does not decode already decoded characters", "[decode]")
{
	CHECK(HtmlDecode("&amp;lt;") == "&lt;");
}
