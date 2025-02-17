#include "textrenderer.h"
#include "QString"

// TextRenderer::TextRenderer() {}

void TextRenderer::populateScene(GameScene *scene, QSharedPointer<GameWorld> gameWorld) {
    QGraphicsSimpleTextItem *textBox = new QGraphicsSimpleTextItem();
    QFont font("Monospace", 13);
    font.setStyleHint(QFont::TypeWriter);
    textBox->setFont(font);

    QString str;

    auto blocks = gameWorld->getMatrixBlocks();
    for (int i = 0; i < blocks.size(); i++) {
        for (int j = 0; j < blocks.at(i).size(); j++) {
            str.append("+---");
        }
        str.append("+\n");
        for (int j = 0; j < blocks.at(i).size(); j++) {
            QSharedPointer<Block> block = blocks.at(i).at(j);
            if (i == gameWorld->getPlayer()->getY() && j == gameWorld->getPlayer()->getX()) {
                str.append("| A ");
            } else if (block->getType() == BlockType::WALL)
                str.append("|███");
            else if (block->getEntity() != nullptr && block->getEntity()->getType() == EntityType::P_TERRAIN)
                str.append("|▒▒▒");
            else if (block->getEntity() != nullptr && block->getEntity()->getType() == EntityType::ENEMY)
                str.append("| E ");
            else if (block->getEntity() != nullptr && block->getEntity()->getType() == EntityType::P_ENEMY)
                str.append("| P ");
            else if (block->getEntity() != nullptr && block->getEntity()->getType() == EntityType::X_ENEMY)
                str.append("| X ");
            else if (block->getEntity() != nullptr && block->getEntity()->getType() == EntityType::HEALTHPACK)
                str.append("| + ");
            else if (block->getEntity() != nullptr && block->getEntity()->getType() == EntityType::ENERGYPACK)
                str.append("|\\/\\");
            else if (block->getEntity() != nullptr && block->getEntity()->getType() == EntityType::PORTAL)
                str.append("| O ");
            else
                str.append("|   ");
        }
        str.append("|\n");
    }
    for (int j = 0; j < blocks.at(0).size(); j++) {
        str.append("+---");
    }
    str.append("+\n");

    textBox->setText(str);
    scene->addItem(textBox);
}
