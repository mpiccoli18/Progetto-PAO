#ifndef MODELLO_H
#define MODELLO_H
#include "sensore.h"
#include <vector>

namespace sensore{
    class modello{
        private:
            std::vector<sensore::Sensore*> InsiemeSensori;
        public:
            modello();
            std::vector<sensore::Sensore*> getInsiemeSens() const;
            void aggiungiSens(Sensore* s);
            void eliminaSens(Sensore* s);
    };
}
#endif // MODELLO_H
