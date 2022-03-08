#include "pch.h"
#include "CppUnitTest.h"

#include "../MovesHistory.h"
#include "../MovesHistory.cpp"
#include "../Figure.cpp"
#include "../Point.cpp"


#include <random>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GameUnitTests
{
	TEST_CLASS(MovesHistoryTests)
	{
	public:

		TEST_METHOD(Test)
		{
			MovesHistory arr;
			std::vector<Move> moves;
			std::vector<Figure*> removed_figures;

			std::default_random_engine gen;
			std::uniform_int_distribution<int> dis(0, 7);

			std::size_t N = 100; // number of inserted items
			// insert items
			for (std::size_t i = 0; i < N; i++) {
				Move move{ Point{dis(gen), dis(gen)}, Point{dis(gen), dis(gen)} };
				Figure* fig = new Figure{ Color::black, FigType::rook, Point{dis(gen), dis(gen)} };

				arr.insert(move, fig);
				moves.push_back(move);
				removed_figures.push_back(fig);

				Assert::AreEqual(i, arr.getCurIndex());
				Assert::AreEqual(false, arr.isEmpty());
				Assert::AreEqual(moves.size(), arr.getSize());
			}

			for (std::size_t i = 0; i < N; i++) {
				Assert::AreEqual(N - i, arr.getSize());
				Assert::AreEqual(N - 1 - i, arr.getCurIndex());

				auto result = arr.undoMove();
				Move move = result.first;
				Figure* fig = result.second;


				Assert::IsTrue(moves[N - 1 - i] == move);
				Assert::IsTrue(removed_figures[N - 1 - i] == fig);

				//	Assert::AreEqual(moves[N - 1 - i], move);
				//	Assert::AreEqual(removed_figures[N - 1 - i], fig);

				if (i == N - 1) { // end, container must be empty
					Assert::AreEqual(true, arr.isEmpty());
				}
				else {
					Assert::AreEqual(false, arr.isEmpty());
					Assert::AreEqual(N - i, arr.getSize() + 1);
					Assert::AreEqual(N - 1 - i, arr.getCurIndex() + 1);
				}
			}

			// need to clean allocated memory
			for (std::size_t i = 0; i < N; i++) {
				delete removed_figures[i];
			}
		}
	};
}
