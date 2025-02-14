﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Windows.Forms;
using System.Drawing.Design;
using System.Drawing.Imaging;

namespace GUIDesigner
{
    public class ImageLocationEditor : UITypeEditor
    {
        // Displays an ellipsis (...) button to start a modal dialog box
        public override UITypeEditorEditStyle GetEditStyle(ITypeDescriptorContext context)
        {
            return UITypeEditorEditStyle.Modal;
        }

        // Edits the value of the specified object using the editor style indicated by the GetEditStyle method.
        public override object EditValue(ITypeDescriptorContext context,
                                         IServiceProvider provider,
                                         object value)
        {
            // Show the dialog we use to open the file.
            // You could use a custom one at this point to provide the file path and the image.
            using (OpenFileDialog openFileDialog = new OpenFileDialog())
            {
                openFileDialog.Filter = "Image files (*.gif;*.jpg;*.jpeg;*.bmp;*.wmf;*.png)|*.gif;*.jpg;*.jpeg;*.bmp;*.wmf;*.png|All files (*.*)|*.*";

                if (openFileDialog.ShowDialog() == DialogResult.OK)
                {
                    Image image = Image.FromFile(openFileDialog.FileName);
                    image.Tag = openFileDialog.FileName;

                    return image;
                }
            }
            return value;
        }

        // Indicates whether the specified context supports painting
        // a representation of an object's value within the specified context.
        public override bool GetPaintValueSupported(ITypeDescriptorContext context)
        {
            return true;
        }

        // Paints a representation of the value of an object using the specified PaintValueEventArgs.
        public override void PaintValue(PaintValueEventArgs e)
        {
            if (e.Value != null)
            {
                // Get image
                Image image = (Image)e.Value;

                // This rectangle indicates the area of the Properties window to draw a representation of the value within.
                Rectangle destRect = e.Bounds;

                // Draw image
                e.Graphics.DrawImage(image, destRect);
            }
        }
    }

    class IconWidget : PictureBox, IWidget
    {
        public IconWidget()
        {
            base.SizeMode = PictureBoxSizeMode.Normal;
            base.Margin = new Padding(0, 0, 0, 0);
            this.Compress = true;
            this.External = false;
            this.Dither = true;
            this.ExternalImage = false;
            this.Stretch = false;
            this.FitToRectange = false;
            this.CutByRectange = false;
            this.Alpha = 255;
            this.TransformType = WidgetTransformType.None;
            this.TransformX = 100;
            this.TransformY = 100;
            this.RotateMask = false;
            this.RotateMaskAngleStart = 0;
            this.RotateMaskAngleEnd = 90;
        }

        [Browsable(false)]
        [DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]
        new public virtual Color BackColor { get; set; }

        [Browsable(false)]
        [DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]
        new public virtual Image BackgroundImage { get; set; }

        [Browsable(false)]
        [DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]
        new public virtual ImageLayout BackgroundImageLayout { get; set; }

        [Browsable(false)]
        [DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]
        new public BorderStyle BorderStyle { get; set; }

        [Browsable(false)]
        [DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]
        new public virtual Cursor Cursor { get; set; }

        [Browsable(false)]
        [DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]
        new public bool UseWaitCursor { get; set; }

        [Browsable(false)]
        [DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]
        new public virtual ContextMenuStrip ContextMenuStrip { get; set; }

        [Browsable(false)]
        [DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]
        new public bool Enabled { get; set; }

        [Browsable(false)]
        [DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]
        new public PictureBoxSizeMode SizeMode { get; set; }

        [Browsable(false)]
        [DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]
        new public string AccessibleDescription { get; set; }

        [Browsable(false)]
        [DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]
        new public string AccessibleName { get; set; }

        [Browsable(false)]
        [DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]
        new public AccessibleRole AccessibleRole { get; set; }

        [Browsable(false)]
        [DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]
        new public Image ErrorImage { get; set; }

        [Editor(typeof(ImageLocationEditor), typeof(UITypeEditor))]
        [DefaultValue(typeof(Image), null)]
        new public Image Image
        {
            get { return base.Image; }
            set { base.Image = value; }
        }

        [Browsable(false)]
        [DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]
        new public string ImageLocation { get; set; }

        [Browsable(false)]
        [DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]
        new public Image InitialImage { get; set; }

        [Browsable(false)]
        [DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]
        new public bool WaitOnLoad { get; set; }

        [Browsable(false)]
        [DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]
        new public virtual AnchorStyles Anchor { get; set; }

        [Browsable(false)]
        [DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]
        new public virtual DockStyle Dock { get; set; }

        [Browsable(false)]
        [DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]
        new public Padding Margin { get; set; }

        [Browsable(false)]
        [DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]
        new public virtual Size MaximumSize { get; set; }

        [Browsable(false)]
        [DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]
        new public virtual Size MinimumSize { get; set; }

        [Browsable(false)]
        [DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]
        new public Padding Padding { get; set; }

        [Browsable(false)]
        [DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]
        new public ControlBindingsCollection DataBindings { get; set; }

        [Browsable(false)]
        [DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]
        new public object Tag { get; set; }

        [LocalizedDescription("PixelFormat", typeof(WidgetManual))]
        public ITU.WidgetPixelFormat PixelFormat { get; set; }
        [LocalizedDescription("Compress", typeof(WidgetManual))]
        public Boolean Compress { get; set; }

        [LocalizedDescription("External", typeof(WidgetManual))]
        public Boolean External { get; set; }
        public Boolean Dither { get; set; }
        [LocalizedDescription("ExternalImage", typeof(WidgetManual))]
        public Boolean ExternalImage { get; set; }

        [LocalizedDescription("Stretch", typeof(WidgetManual))]
        public Boolean Stretch
        {
            get { return base.SizeMode == PictureBoxSizeMode.StretchImage; }
            set { base.SizeMode = value ? PictureBoxSizeMode.StretchImage : PictureBoxSizeMode.Normal; }
        }

        [LocalizedDescription("FitToRectange", typeof(WidgetManual))]
        public Boolean FitToRectange { get; set; }
        [LocalizedDescription("CutByRectange", typeof(WidgetManual))]
        public Boolean CutByRectange { get; set; }
        [LocalizedDescription("Angle", typeof(WidgetManual))]
        public int Angle { get; set; }
        [LocalizedDescription("Alpha", typeof(WidgetManual))]
        public byte Alpha { get; set; }

        [LocalizedDescription("FilePath", typeof(WidgetManual))]
        public string FilePath
        {
            get
            {
                if (this.ExternalImage)
                    return this.Name;

                return "";
            }

            set
            {
                if (this.ExternalImage)
                    this.Name = value;
            }
        }

        [LocalizedDescription("RotateMask", typeof(WidgetManual))]
        public bool RotateMask { get; set; }

        private int start_rm_angle_t = 0;
        [LocalizedDescription("RotateMaskAngleStart", typeof(WidgetManual))]
        public int RotateMaskAngleStart
        {
            get { return start_rm_angle_t; }
            set
            {
                if (value < 0)
                {
                    start_rm_angle_t = 0;
                }
                else if (value > 360)
                {
                    start_rm_angle_t = 360;
                }
                else if (value >= this.RotateMaskAngleEnd)
                {
                    start_rm_angle_t = (this.RotateMaskAngleEnd > 0) ? (this.RotateMaskAngleEnd - 1) : (0);
                }
                else
                {
                    start_rm_angle_t = value;
                }
            }
        }

        private int end_rm_angle_t = 90;
        [LocalizedDescription("RotateMaskAngleEnd", typeof(WidgetManual))]
        public int RotateMaskAngleEnd
        {
            get { return end_rm_angle_t; }
            set
            {
                if (value < 0)
                {
                    end_rm_angle_t = 0;
                }
                else if (value > 360)
                {
                    end_rm_angle_t = 360;
                }
                else if (value <= this.RotateMaskAngleStart)
                {
                    end_rm_angle_t = (this.RotateMaskAngleStart <= 359) ? (this.RotateMaskAngleStart + 1) : (360);
                }
                else
                {
                    end_rm_angle_t = value;
                }
            }
        }

        public enum WidgetTransformType : uint
        {
            None        = 0,
            TurnLeft    = 1,
            TurnTop     = 2,
            TurnRight   = 3,
            TurnBottom  = 4
        }

        [LocalizedDescription("TransformType", typeof(WidgetManual))]
        public WidgetTransformType TransformType { get; set; }

        private int transformX = 0;
        [LocalizedDescription("TransformX", typeof(WidgetManual))]
        public int TransformX {
            get
            {
                return transformX;
            }

            set
            {
                if (value < 0)
                    transformX = 0;
                else if (value > ITU.ITU_TRANSFORM_MAX_VALUE)
                    transformX = ITU.ITU_TRANSFORM_MAX_VALUE;
                else
                    transformX = value;
            }
        }

        private int transformY = 0;
        [LocalizedDescription("TransformY", typeof(WidgetManual))]
        public int TransformY
        {
            get
            {
                return transformY;
            }

            set
            {
                if (value < 0)
                    transformY = 0;
                else if (value > ITU.ITU_TRANSFORM_MAX_VALUE)
                    transformY = ITU.ITU_TRANSFORM_MAX_VALUE;
                else
                    transformY = value;
            }
        }

        private bool hided = false;
        [LocalizedDescription("Hided", typeof(WidgetManual))]
        public bool Hided
        {
            get
            {
                return hided;
            }

            set
            {
                if (value)
                    Hide();
                else
                    Show();

                hided = value;
            }
        }

        private bool hide_ds = false;
        public bool HideDS
        {
            get
            {
                return hide_ds;
            }
            set
            {
                hide_ds = value;
            }
        }

        public ITUWidget CreateITUWidget()
        {
            ITUIcon widget = new ITUIcon();

            widget.name = this.Name;

            if (this.FilePath.Length > 0)
                widget.name = this.FilePath;

            PropertyDescriptorCollection properties = TypeDescriptor.GetProperties(this);
            widget.visible = (bool)properties["Visible"].GetValue(this);

            widget.active = false;
            widget.dirty = false;
            widget.alpha = 255;
            widget.rect.x = this.Location.X;
            widget.rect.y = this.Location.Y;
            widget.rect.width = this.Size.Width;
            widget.rect.height = this.Size.Height;
            widget.color.alpha = this.Alpha;
            widget.color.red = 0;
            widget.color.green = 0;
            widget.color.blue = 0;
            widget.bound.x = 0;
            widget.bound.y = 0;
            widget.bound.width = 0;
            widget.bound.height = 0;

            if (this.ExternalImage)
                widget.flags |= ITU.ITU_EXTERNAL_IMAGE;

            if (this.Image != null)
            {
                widget.staticSurf = ITU.CreateSurfaceNode(this.Image as Bitmap, this.PixelFormat, this.Compress, this.External, this.Dither);
            }
            if (this.External)
                widget.flags |= ITU.ITU_EXTERNAL;

            if (this.Stretch)
            {
                widget.flags |= ITU.ITU_STRETCH;
            }
            if (this.FitToRectange)
            {
                widget.flags |= ITU.ITU_FIT_TO_RECT;
            }
            if (this.CutByRectange)
            {
                widget.flags |= ITU.ITU_CUT_BY_RECT;
            }
            widget.angle = this.Angle;
            widget.transformType = (ITUTransformType)this.TransformType;
            widget.transformX = this.TransformX;
            widget.transformY = this.TransformY;

            widget.use_rotate_mask = (this.RotateMask) ? (1) : (0);
            widget.start_rm_angle = this.RotateMaskAngleStart;
            widget.end_rm_angle = this.RotateMaskAngleEnd;

            return widget;
        }

        public void SaveImages(String path)
        {
            if (this.Image != null)
            {
                Bitmap bitmap = this.Image as Bitmap;
                ITU.SaveImage(bitmap, path , LayerWidget.FindLayerName(this), this.Name + "_Image");
            }
        }

        public void WriteFunctions(HashSet<string> functions)
        {
        }

        public bool HasFunctionName(string funcName)
        {
            return false;
        }
    }
}
