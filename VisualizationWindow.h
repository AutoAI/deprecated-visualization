#include <QGLWidget>
#include <QWidget>

class VisualizationWindow : public QGLWidget {
	Q_OBJECT

	public:
		VisualizationWindow(QWidget *p = 0);
		bool initFrames();

};
