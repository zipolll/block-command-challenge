#include "declaration.h"
using namespace sf;
using namespace std;
/* ===== 关卡通过状态（由文件读取） ===== */
static bool levelPassed[4] = { false, false, false, false };
/* ===== 从 levelpass.txt 读取 ===== */
static void loadLevelPassed() {
    ifstream fin("levelpass.txt");
    if (!fin.is_open()) {
        // 文件不存在：默认只能从第一关开始
        return;
    }

    for (int i = 0; i < 4; ++i) {
        int x;
        if (fin >> x)
            levelPassed[i] = (x != 0);
        else
            levelPassed[i] = false;
    }
    fin.close();
}

/* ===== 是否解锁 ===== */
static bool isUnlocked(int level) {
    if (level == 1) return true;
    return levelPassed[level - 2];
}

/* ===== 圆角矩形 ===== */
static ConvexShape makeRoundedRect(float w, float h, float r) {
    ConvexShape s(8);
    s.setPoint(0, { r, 0 });
    s.setPoint(1, { w - r, 0 });
    s.setPoint(2, { w, r });
    s.setPoint(3, { w, h - r });
    s.setPoint(4, { w - r, h });
    s.setPoint(5, { r, h });
    s.setPoint(6, { 0, h - r });
    s.setPoint(7, { 0, r });
    return s;
}

/* ===== 关卡按钮 ===== */
class LevelButton {
private:
    ConvexShape box;
    Text title;
    Text status;
    int level;
    bool unlocked = false;
    bool passed = false;

public:
    LevelButton(Vector2f pos, float size, int id, Font& font)
        : level(id) {

        box = makeRoundedRect(size, size, 26.f);
        box.setPosition(pos);
        box.setOutlineThickness(3);
        box.setOutlineColor(Color(220, 220, 240));

        title.setFont(font);
        title.setCharacterSize(34);
        title.setFillColor(Color::White);

        status.setFont(font);
        status.setCharacterSize(24);

        update();
    }

    void update() {
        unlocked = isUnlocked(level);
        passed = levelPassed[level - 1];

        if (!unlocked) {
            box.setFillColor(Color(70, 70, 80));
            status.setString("LOCKED");
            status.setFillColor(Color(200, 200, 210));
        }
        else if (passed) {
            box.setFillColor(Color(46, 139, 87));
            status.setString("COMPLETED");
            status.setFillColor(Color::White);
        }
        else {
            box.setFillColor(Color(72, 118, 255));
            status.setString("AVAILABLE");
            status.setFillColor(Color::White);
        }

        title.setString("LEVEL " + to_string(level));

        FloatRect tb = title.getLocalBounds();
        title.setOrigin(tb.left + tb.width / 2, tb.top + tb.height / 2);
        title.setPosition(
            box.getPosition().x + box.getGlobalBounds().width / 2,
            box.getPosition().y + 52
        );

        FloatRect sb = status.getLocalBounds();
        status.setOrigin(sb.left + sb.width / 2, sb.top + sb.height / 2);
        status.setPosition(
            box.getPosition().x + box.getGlobalBounds().width / 2,
            box.getPosition().y + box.getGlobalBounds().height - 52
        );
    }

    void draw(RenderWindow& win) {
        win.draw(box);
        win.draw(title);
        win.draw(status);
    }

    bool hit(Vector2f p) const {
        return box.getGlobalBounds().contains(p);
    }

    bool clickable() const {
        return unlocked;
    }

    int getLevel() const {
        return level;
    }
};

/* ===== 选关界面 ===== */
int levelchoose() {

    /* ===== 读取通关文件 ===== */
    loadLevelPassed();

    RenderWindow window(VideoMode(1280, 900), "Level Select");
    window.setFramerateLimit(60);

    Font font;
    if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
        return -1;
    }

    /* ===== 标题 ===== */
    Text title("BLOCK CHALLENGE", font, 72);
    title.setFillColor(Color(255, 215, 0));
    FloatRect tb = title.getLocalBounds();
    title.setOrigin(tb.left + tb.width / 2, tb.top);
    title.setPosition(640, 30);

    /* ===== 解锁规则 ===== */
    Text unlockRule(
        "Unlock subsequent levels by completing previous levels.",
        font,
        32
    );
    unlockRule.setFillColor(Color::White);
    unlockRule.setPosition(640, 200);
    unlockRule.setOrigin(
        unlockRule.getLocalBounds().left +
        unlockRule.getLocalBounds().width / 2,
        unlockRule.getLocalBounds().top +
        unlockRule.getLocalBounds().height / 2
    );

    FloatRect urG = unlockRule.getGlobalBounds();
    RectangleShape unlockBg(
        Vector2f(urG.width + 40, urG.height + 20)
    );
    unlockBg.setFillColor(Color(70, 130, 180));
    unlockBg.setPosition(urG.left - 20, urG.top - 10);

    /* ===== 按钮 ===== */
    vector<LevelButton> buttons;
    float size = 220;
    float gap = 80;
    Vector2f start(320, 230);

    int id = 1;
    for (int r = 0; r < 2; ++r) {
        for (int c = 0; c < 2; ++c) {
            buttons.emplace_back(
                Vector2f(
                    start.x + c * (size + gap),
                    start.y + r * (size + gap)
                ),
                size,
                id++,
                font
            );
        }
    }

    /* ===== Input Rule（保持不变） ===== */
    Text inputRule(
        "C++ / SFML Programming Project",
        font,
        36
    );
    inputRule.setFillColor(Color::White);
    inputRule.setPosition(640, 880);
    inputRule.setOrigin(
        inputRule.getLocalBounds().left +
        inputRule.getLocalBounds().width / 2,
        inputRule.getLocalBounds().top +
        inputRule.getLocalBounds().height
    );

    FloatRect irG = inputRule.getGlobalBounds();
    RectangleShape inputBg(
        Vector2f(irG.width + 50, irG.height + 30)
    );
    inputBg.setFillColor(Color(70, 130, 180));
    inputBg.setPosition(irG.left - 25, irG.top - 15);

    /* ===== 主循环 ===== */
    while (window.isOpen()) {
        Event e;
        while (window.pollEvent(e)) {
            if (e.type == Event::Closed) {
                window.close();
                return -1;
            }

            if (e.type == Event::MouseButtonPressed) {
                Vector2f mp = window.mapPixelToCoords(Mouse::getPosition(window));
                for (auto& b : buttons) {
                    if (b.hit(mp) && b.clickable()) {
                        window.close();
                        return b.getLevel();
                    }
                }
            }
        }

        window.clear(Color(25, 25, 40));
        window.draw(title);
        window.draw(unlockBg);
        window.draw(unlockRule);
        for (auto& b : buttons) b.draw(window);
        window.draw(inputBg);
        window.draw(inputRule);
        window.display();
    }

    return -1;
}
