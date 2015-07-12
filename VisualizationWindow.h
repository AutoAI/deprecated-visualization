#include <QGLWidget>
#include <QWidget>

class VisualizationWindow : public QGLWidget {
	Q_OBJECT

	public:
		VisualizationWindow(QWidget *p = 0);
		bool initFrames();
	
	protected:
		void initializeGL();
		void resizeGL(int w, int h);
		void paintGL();

	private:
		uint32_t width;
		uint32_t height;

		uint8_t *grayData;
		uint16_t *clusters;
};
